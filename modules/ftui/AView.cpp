// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:20 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/07 15:45:03 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <exception>
#include <cstdlib>

#include "ft/utils.hpp"
#include "ft/padformat.hpp"
#include "ft_xml/XmlParser.hpp"

#include "ftui/AView.hpp"
#include "ftui/Activity.hpp"
#include "ftui/ALayout.hpp"

using std::string;

namespace ftui
{

/*
** ========================================================================== **
** CONSTRUCTION
*/

AView::AView(Activity &act, std::string const &viewName) :
	_holder(nullptr),
	_act(act),
	_id(nullptr),
	_flags(0),
	_luaCallbacks(0),
	_alpha(1.f)
{
	lua_State *const	l = act.getLuaState();

	ftlua::push(l, ftlua::newtab);
	ftlua::push(l, ftlua::makeKeys(viewName));
	lua_setmetatable(l, -2);
	ftlua::set(l, -1, 0, ftlua::light(this));
	ftlua::set(l, ftlua::light(this), ftlua::dup(-3));
	lua_pop(l, -1);
	return ;
}

AView::~AView(void)
{
	if (_id != nullptr)
		delete _id;
}

void				AView::inflate(ViewTemplate const &t,
						ParamMap const *parent_map)
{
	inflateParams(t.getParams(), parent_map);
	if (t.getChilds().size() > 0)
		throw std::runtime_error(ft::f("A simple view (#%) cannot have child "
				"(inherited from template)", (_id == nullptr) ? "" : *_id));
}

void				AView::inflate(ft::XmlParser &xml,
						ParamMap const *parent_map)
{
	ft::XmlParser::State	state;

	inflateParams(xml.getParams(), parent_map);
	if (!xml.next(state))
		FTASSERT(false);
	FTASSERT(state == ft::XmlParser::State::END);
	return ;
}

void				AView::inflateParams(param_map_t const &params,
						ParamMap const *parent_map)
{
	static const std::string	parent_var("$parent");
	ParamMap					param_map(params, parent_map);

	for (auto const &param : params)
	{
		if (param.first == "inherit")
		{
			std::stringstream	ss(param.second);
			char				buff[64];
			ViewTemplate const	*tmpl;

			while (ss.getline(buff, sizeof(buff), ' '))
			{
				tmpl = _act.getViewTemplate(std::string(buff));
				if (tmpl == nullptr)
					throw std::runtime_error(ft::f("Unknown template: %",
						buff));
				inflate(*tmpl, &param_map);
			}
		}
		else
			setParam2(param.first, param.second, &param_map);
	}
}

void				AView::setParam2(std::string const &key,
						std::string const &value, ParamMap const *param_map)
{
	static const std::string	parent_var("$parent");
	std::string::size_type		pos;
	std::string					tmp_val(value);

	pos = 0;
	while ((pos = value.find(parent_var, pos)) != std::string::npos)
	{
		std::string const	*parent_value;

		if ((param_map = param_map->prev) == nullptr
			|| (parent_value = param_map->find(key)) == nullptr)
			throw std::runtime_error(ft::f("Parent does not have a % param"
					" (#%)", key, (_id == nullptr) ? "" : *_id));
		tmp_val.replace(pos, parent_var.size(), *parent_value);
		pos += parent_value->size();
	}
	setParam(key, tmp_val);
}

/*
** ========================================================================== **
** View core
*/
std::string			AView::tostring(void) const
{
	return ft::truncmid(this->_id != nullptr ? *_id : "noname", 20);
}

std::string const	*AView::getId(void) const
{
	return (this->_id);
}

ALayout				*AView::getParent(void)
{
	return ((this->_holder == nullptr) ? nullptr : this->_holder->getParent());
}

IViewHolder			*AView::getViewHolder(void)
{
	return (this->_holder);
}

IViewHolder const	*AView::getViewHolder(void) const
{
	return (this->_holder);
}

void				AView::setId(std::string const &id)
{
	lua_State *const	l = _act.getLuaState();

	if (_id != nullptr)
		throw std::runtime_error(ft::f("Id set twice (#%)", *_id));
	_id = new std::string(id);
	ftlua::push(l, this); // TODO assert 'this'
	lua_setglobal(l, _id->c_str());
}

void				AView::setMouseOver(int x, int y, bool state)
{
	if (static_cast<bool>(this->_flags & AView::MOUSE_OVER) != state)
	{
		if (state == true)
		{
			this->_flags |= AView::MOUSE_OVER;
			this->onMouseEnter(x, y);
		}
		else
		{
			this->_flags &= ~AView::MOUSE_OVER;
			this->onMouseLeave(x, y);
		}
	}
	return ;
}

void				AView::setViewHolder(IViewHolder *holder)
{
	if (holder == nullptr)
	{
		if (this->isAttached())
			this->setAttached(false);
		this->_holder = holder;
	}
	else
	{
		if (holder->getParent() == nullptr
			|| !holder->getParent()->isAttached())
		{
			if (this->isAttached())
				this->setAttached(false);
			this->_holder = holder;
		}
		else
		{
			this->_holder = holder;
			if (!this->isAttached())
				this->setAttached(true);
		}
	}
	return ;
}

void				AView::setAttached(bool state)
{
	if (static_cast<bool>(this->_flags & AView::ATTACHED) != state)
	{
		if (state == true)
		{
			this->_flags |= AView::ATTACHED;
			this->onAttach();
		}
		else
		{
			this->_flags &= ~AView::ATTACHED;
			this->onDetach();
		}
	}
	return ;
}


/*
** ========================================================================== **
** View properties
*/
float				AView::getAlpha(void) const
{
	return (this->_alpha);
}

bool				AView::isVisible(void) const
{
	return (!(this->_flags & AView::HIDDEN));
}

void				AView::setAlpha(float value)
{
	this->_alpha = value;
	return ;
}

void				AView::setVisibility(bool show)
{
	if (this->isVisible() != show)
	{
		if (show == true)
			this->_flags &= ~AView::HIDDEN;
		else
			this->_flags |= AView::HIDDEN;
		onVisibilityChange(show);
	}
	return ;
}

bool				AView::isMouseOver(void) const
{
	return (this->_flags & AView::MOUSE_OVER);
}

bool				AView::isAttached(void) const
{
	return (this->_flags & AView::ATTACHED);
}

void				AView::setParam(string const &k, string const &v)
{
	static std::unordered_map<std::string, void (*)(AView*,
		std::string const &)> const		param_map
	{
		{"id", [](AView *view, std::string const &p)
		{
			view->setId(p);
		}},
		{"alpha", [](AView *view, std::string const &p)
		{
			view->setAlpha(std::atof(p.c_str()));
		}},
		{"visibility", [](AView *view, std::string const &p)
		{
			view->setVisibility(p == "true");
		}},
		{"mouse_scroll_target", [](AView *view, std::string const &p)
		{
			view->hookMouseScroll(p == "true");
		}},
		{"mouse_click_target", [](AView *view, std::string const &p)
		{
			view->hookMouseClick(p == "true");
		}},
		{"mouse_move_target", [](AView *view, std::string const &p)
		{
			view->hookMouseMove(p == "true");
		}},
		{"keyboard_target", [](AView *view, std::string const &p)
		{
			view->hookKeyboard(p == "true");
		}},
		{"activity_scripts", [](AView *view, std::string const &p)
		{
			view->_act.saveScriptPath(p);
		}},
		{"parentKey", [](AView *view, std::string const &p)
		{
			AView *const		parent = view->getParent();
			lua_State *const	l = view->_act.getLuaState();

			if (parent == nullptr)
				throw std::runtime_error(ft::f("parentKey used on unattached "
					"view (#%)", (view->_id == nullptr) ? "" : *view->_id));
			// parent[p] = view
			ftlua::push(l, parent);
			ftlua::set(l, -1, p, view);
			// TODO: WTF? ftlua::set(l, ftlua::lightKey(parent), p, view)
			lua_pop(l, -1);
		}},
	};
	auto const		&it = param_map.find(k);

	if (it != param_map.end())
		it->second(this, v);
	else if (_holder != NULL)
		_holder->setParam(k, v);
	return ;
}

/*
** ========================================================================== **
** Callbacks
*/
/*
** Queries callbacks
*/
void				AView::onUpdate(void)
{
	this->_flags &= ~AView::UPDATE_QUERY;
	this->callLuaCallback(_act.getLuaState(), LuaCallback::UPDATE);
	return ;
}

void				AView::onMeasure(void)
{
	this->_flags &= ~AView::MEASURE_QUERY;
	this->callLuaCallback(_act.getLuaState(), LuaCallback::MEASURE);
}

void				AView::onDraw(ACanvas &canvas)
{
	this->_flags &= ~AView::REDRAW_QUERY;
	this->callLuaCallback(_act.getLuaState(), LuaCallback::DRAW
						  , &canvas);
	return ;
}

/*
** Low level callbacks
*/
bool				AView::onMouseScroll(int x, int y, float delta)
{
	if (this->callLuaCallback(
			_act.getLuaState(), LuaCallback::MOUSE_SCROLL, x, y, delta))
		return (true);
	return (false);
}

bool				AView::onMouseDown(int x, int y, int button, int mods)
{
	if (this->callLuaCallback(
			_act.getLuaState(), LuaCallback::MOUSE_DOWN, x, y, button, mods))
		return (true);
	return (false);
}

bool				AView::onMouseUp(int x, int y, int button, int mods)
{
	if (this->callLuaCallback(
			_act.getLuaState(), LuaCallback::MOUSE_UP, x, y, button, mods))
		return (true);
	return (false);
}

bool				AView::onMouseMove(int x, int y)
{
	if (this->callLuaCallback(
			_act.getLuaState(), LuaCallback::MOUSE_MOVE, x, y))
		return (true);
	return (false);
}

bool				AView::onKeyDown(int key_code, int mods)
{
	if (this->callLuaCallback(
			_act.getLuaState(), LuaCallback::KEY_DOWN, key_code, mods))
		return (true);
	return (false);
}

bool				AView::onKeyUp(int key_code, int mods)
{
	if (this->callLuaCallback(
			_act.getLuaState(), LuaCallback::KEY_UP, key_code, mods))
		return (true);
	return (false);
}

/*
** High level callbacks
*/
void				AView::onMouseEnter(int x, int y)
{
	this->callLuaCallback(_act.getLuaState(), LuaCallback::MOUSE_ENTER, x, y);
	return ;
}
void				AView::onMouseLeave(int x, int y)
{
	this->callLuaCallback(_act.getLuaState(), LuaCallback::MOUSE_LEAVE, x, y);
	return ;
}
void				AView::onAttach(void)
{
	this->callLuaCallback(_act.getLuaState(), LuaCallback::ATTACH);
	return ;
}
void				AView::onDetach(void)
{
	this->callLuaCallback(_act.getLuaState(), LuaCallback::DETACH);
	return ;
}
void				AView::onPositionChange(void)
{
	this->callLuaCallback(_act.getLuaState(), LuaCallback::POSITION_CHANGE);
	return ;
}
void				AView::onSizeChange(ft::Vec2<int> size)
{
	this->callLuaCallback(
		_act.getLuaState(), LuaCallback::SIZE_CHANGE, size.x, size.y);
	return ;
}
void				AView::onVisibilityChange(bool hidden)
{
	this->callLuaCallback(
		_act.getLuaState(), LuaCallback::VISIBILITY_CHANGE, hidden);
	return ;
}

/*
** set callback
*/
void				AView::setLuaCallback(lua_State *l)
{
	char const *const	callback = luaL_checkstring(l, -2);
	auto const			&it = Activity::callback_map.find(std::string(callback));
	uint32_t			callbackId;

	if (it == Activity::callback_map.end())
		luaL_error(l, "AView::setLuaCallback: "
				   "Unknow lua callback: %", callback);
	callbackId = it->second;
	ftlua::set(l, 1, callbackId, ftlua::dup(-2));
	if (lua_isfunction(l, -1))
		_luaCallbacks |= 1 << callbackId;
	else
		_luaCallbacks &= ~(1 << callbackId);
	lua_pop(l, 3);
}

void				AView::registerEvent(std::string const &name)
{
	_act.registerEvent(name, this);
	return ;
}

void				AView::unregisterEvent(std::string const &name)
{
	_act.unregisterEvent(name, this);
	return ;
}


/*
** ========================================================================== **
** Layout system
*/
/*
** Targets
*/
bool				AView::isMouseScrollTargeted(void) const
{ return (this->_flags & AView::MOUSE_SCROLL_TARGET); }
bool				AView::isMouseClickTargeted(void) const
{ return (this->_flags & AView::MOUSE_CLICK_TARGET); }
bool				AView::isMouseMoveTargeted(void) const
{ return (this->_flags & AView::MOUSE_MOVE_TARGET); }
bool				AView::isMouseCaptureTargeted(void) const
{ return (this->_flags & AView::MOUSE_CAPTURE_TARGET); }
bool				AView::isKeyboardTargeted(void) const
{ return (this->_flags & AView::KEYBOARD_TARGET); }

/*
** Queries
*/
bool				AView::isUpdateQueried(void) const
{ return (this->_flags & AView::UPDATE_QUERY); }
bool				AView::isMeasureQueried(void) const
{ return (this->_flags & AView::MEASURE_QUERY); }
bool				AView::isRedrawQueried(void) const
{ return (this->_flags & AView::REDRAW_QUERY); }

/*
** View core
*/
/*
** ========================================================================== **
** Register target
** Some low level callbacks are not enabled by default
*/
void			AView::hookMouseScroll(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_flags & AView::MOUSE_SCROLL_TARGET) != state)
	{
		if (state == true)
			this->_flags |= AView::MOUSE_SCROLL_TARGET;
		else
			this->_flags &= ~AView::MOUSE_SCROLL_TARGET;
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseScroll(state);
	}
	return ;
}

void			AView::hookMouseClick(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_flags & AView::MOUSE_CLICK_TARGET) != state)
	{
		if (state == true)
			this->_flags |= AView::MOUSE_CLICK_TARGET;
		else
			this->_flags &= ~AView::MOUSE_CLICK_TARGET;
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseClick(state);
	}
	return ;
}

void			AView::hookMouseMove(bool state)
{
	ALayout			*p;

	// FTPADB("%", (_id ? *_id : "noname"));
	if (static_cast<bool>(this->_flags & AView::MOUSE_MOVE_TARGET) != state)
	{
		// FTPAD("ENTERING");
		if (state == true)
			this->_flags |= AView::MOUSE_MOVE_TARGET;
		else
			this->_flags &= ~AView::MOUSE_MOVE_TARGET;
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseMove(state);
	}
	// FTPADE();
	return ;
}

void			AView::hookMouseCapture(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_flags & AView::MOUSE_CAPTURE_TARGET) != state)
	{
		if (state == true)
			this->_flags |= AView::MOUSE_CAPTURE_TARGET;
		else
			this->_flags &= ~AView::MOUSE_CAPTURE_TARGET;
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseCapture(state);
	}
	return ;
}

void			AView::hookKeyboard(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_flags & AView::KEYBOARD_TARGET) != state)
	{
		if (state == true)
			this->_flags |= AView::KEYBOARD_TARGET;
		else
			this->_flags &= ~AView::KEYBOARD_TARGET;
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetKeyboard(state);
	}
	return ;
}

/*
** ========================================================================== **
** Query
** Queries a callback for the next frame
*/
void			AView::queryUpdate(void)
{
	ALayout		*p;

	if ((this->_flags & AView::UPDATE_QUERY) != AView::UPDATE_QUERY)
	{
		this->_flags |= AView::UPDATE_QUERY;
		p = this->getParent();
		if (p != nullptr)
			p->spreadQueryUpdate();
	}
	return ;
}

void			AView::queryMeasure(void)
{
	ALayout		*p;

	if ((this->_flags & AView::MEASURE_QUERY) != AView::MEASURE_QUERY)
	{
		this->_flags |= AView::MEASURE_QUERY;
		p = this->getParent();
		if (p != nullptr)
			p->spreadQueryMeasure();
	}
	return ;
}

void			AView::queryRedraw(void)
{
	ALayout		*p;

	if ((this->_flags & AView::REDRAW_QUERY) != AView::REDRAW_QUERY)
	{
		this->_flags |= AView::REDRAW_QUERY;
		p = this->getParent();
		if (p != nullptr)
			p->spreadQueryRedraw();
	}
	return ;
}

/*
** ========================================================================== **
** AView::ParamMap
*/

AView::ParamMap::ParamMap(param_map_t const &params, ParamMap const *prev) :
	params(params),
	prev(prev)
{
}

AView::ParamMap::~ParamMap(void)
{
}

std::string const	*AView::ParamMap::find(std::string const &key) const
{
	for (auto const &p : params)
	{
		if (p.first == key)
			return (&(p.second));
	}
	return (nullptr);
}

};
