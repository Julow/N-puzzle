// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:20 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/11 17:56:43 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <exception>
#include <cstdlib>
#include <iostream>

#include "ft/utils.hpp"
#include "ftlua/ftlua.hpp"
#include "ftui/AView.hpp"
#include "ftui/Activity.hpp"
#include "ftui/ALayout.hpp"
#include "ftui/IViewHolder.hpp"
#include "ftui/EventParams.hpp"
#include "ftui/XmlParser.hpp"
#include "ftui/VerticalLayout.hpp"

#include "ftui/templates/AView_callLuaCallback.tpp"

using std::string;

namespace ftui
{

/*
** ========================================================================== **
** Init-time -> instance.CTOR from xml parsing
*/

static std::string const	*retrieve_id(XmlParser const &xml)
{
	auto const		&it = xml.getParams().find("id");

	if (it != xml.getParams().end())
		return (new std::string(it->second));
	return (nullptr);
}

AView::AView(XmlParser const &xml, Activity &act) :
	_holder(nullptr),
	_act(act),
	_id(retrieve_id(xml)),
	_flags(0),
	_luaCallbacks(0),
	_alpha(1.f)
{
	lua_State *const	l = act.getLuaState();
	int					err;

	(void)lua_getglobal(l, "ft");
	(void)lua_pushstring(l, "push_view");
	(void)lua_gettable(l, -2);
	err = lua_getglobal(l, xml.getMarkupName().c_str());
	FTASSERT(err == LUA_TTABLE);
	lua_pushlightuserdata(l, this);
	if (_id != nullptr)
		(void)lua_pushstring(l, _id->c_str());
	else
		lua_pushnil(l);
	err = lua_pcall(l, 3, 0, 0);
	FTASSERT(err == LUA_OK);
	lua_pop(l, 1);
	return ;
}

/*
** ========================================================================== **
** Render-time -> instance.CTOR from specific request NYI
** TODO: Implement
*/

/*
** ========================================================================== **
** End-time -> instance.DTOR from activity or parent
*/

AView::~AView(void)
{
	if (_id != nullptr)
		delete _id;
}

/*
** ========================================================================== **
** View core
*/
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

void				AView::setViewHolder(IViewHolder *holder)
{
	FTASSERT(this->_holder == nullptr);
	this->_holder = holder;
	return ;
}

void				AView::inflate(XmlParser &xml, Activity &)
{
	XmlParser::State	state;

	for (auto const &p : xml.getParams())
		setParam(p.first, p.second);
	if (!xml.next(state))
		FTASSERT(false);
	FTASSERT(state == XmlParser::State::END);
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
	return (this->_flags & AView::HIDDEN);
}

void				AView::setAlpha(float value)
{
	this->_alpha = value;
	return ;
}

void				AView::setVisibility(bool hidden)
{
	if (static_cast<bool>(this->_flags & AView::HIDDEN) != hidden)
	{
		if (hidden == true)
			this->_flags |= AView::HIDDEN;
		else
			this->_flags &= ~AView::HIDDEN;
		onVisibilityChange(hidden);
	}
	return ;
}

bool				AView::isMouseOver(void) const
{
	return (this->_flags & AView::MOUSE_OVER);
}

void				AView::setParam(string const &k, string const &v)
{
	static std::unordered_map<std::string, void (*)(AView*,
		std::string const &)> const		param_map
	{
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

void				AView::onDraw(Canvas &canvas)
{
	uint32_t const		id = static_cast<uint32_t>(LuaCallback::DRAW);
	lua_State			*l;

	FTPAD("%", (_id ? *_id : "noname"));
	this->_flags &= ~AView::REDRAW_QUERY;
	if (!(_luaCallbacks & (1 << id)))
		return ;
	l = _act.getLuaState();
	lua_pushglobaltable(l);							// _G
	lua_pushlightuserdata(l, this);					// this, _G
	if (lua_gettable(l, -2) != LUA_TTABLE)			// [], _G
		throw std::runtime_error("Lua missing table");
	lua_pushinteger(l, id);							// callback_id, [], _G
	if (lua_gettable(l, -2) != LUA_TFUNCTION)		// fun, [], _G
		throw std::runtime_error("Lua missing callback");
	lua_pushvalue(l, -2);							// [], fun, [], _G

	lua_pushlightuserdata(l, &canvas);				// &can, [], fun, [], _G
	if (lua_gettable(l, -5) != LUA_TTABLE)			// [c], [], fun, [], _G
		throw std::runtime_error("Lua missing canvas table");
	if (lua_pcall(l, 2, 0, 0))						// [], _G
		throw std::runtime_error(ft::f("Lua: %", luaL_checkstring(l, -1)));
	lua_pop(l, 2);									// empty
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
void				AView::onEvent(std::string const &event, IEventParams *p)
{
	this->callLuaCallback(_act.getLuaState(), LuaCallback::EVENT, event);
	(void)p;// TODO: onEvent IEventParams
	return ;
}
void				AView::onPositionChange(void)
{
	this->callLuaCallback(_act.getLuaState(), LuaCallback::POSITION_CHANGE);
	return ;
}
void				AView::onSizeChange(void)
{
	ft::Vec2<int>	size = this->getViewHolder()->getSize();

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
	auto const			&it = AView::callback_map.find(std::string(callback));
	uint32_t			callbackId;

	if (it == AView::callback_map.end())
		luaL_error(l, "Unknow lua callback: %s", callback);
	callbackId = it->second;
	lua_pushinteger(l, callbackId);		// <-	id, f, name, view_table
	lua_pushvalue(l, -2);				// <-	f, id, f, name, view_table
	lua_settable(l, -5);				// <-	f, name, view_table
	if (lua_isfunction(l, -1))
		_luaCallbacks |= 1 << callbackId;
	else
		_luaCallbacks &= ~(1 << callbackId);
	lua_pop(l, 3);
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

	FTPADB("%", (_id ? *_id : "noname"));
	if (static_cast<bool>(this->_flags & AView::MOUSE_MOVE_TARGET) != state)
	{
		FTPAD("ENTERING");
		if (state == true)
			this->_flags |= AView::MOUSE_MOVE_TARGET;
		else
			this->_flags &= ~AView::MOUSE_MOVE_TARGET;
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseMove(state);
	}
	FTPADE();
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

	ft::f(std::cout, "Query redraw %\n", (_id ? *_id : "noname"));
	if ((this->_flags & AView::REDRAW_QUERY) != AView::REDRAW_QUERY)
	{
		this->_flags |= AView::REDRAW_QUERY;
		p = this->getParent();
		if (p != nullptr)
			p->spreadQueryRedraw();
	}
	return ;
}

};
