// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:27 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/21 18:00:15 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <algorithm>
#include <iostream>

#include "ft/utils.hpp"
#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/Canvas.hpp"
#include "ft_xml/XmlParser.hpp"

namespace ftui
{


// ========================================================================== //
// CONSTRUCTION
//

// CTOR / DTOR ====================== //
Activity::Activity(ft::Vec2<int> size) :
	_rootView(NULL),
	_eventMap(),
	_size(size),
	_l(nullptr)
{
	return ;
}

Activity::~Activity(void)
{
	if (_l != nullptr)
		lua_close(_l);
	// TODO: release views
	return ;
}

// INFLATE ========================== //
static lua_State	*new_lua_env()
{
	lua_State *const	l = luaL_newstate();
	int					err{0};

	if (l == nullptr)
		throw std::runtime_error("Error while creating lua state");
	luaL_openlibs(l);
	err = luaL_dofile(l, (RES_PATH "/utils.lua"));
	FTASSERT(err == LUA_OK);
	ftlua::registerLuaCFunTable(l, "_G", "createView", &Activity::createViewG);
	ftlua::pushUtils(l);
	Canvas::pushTemplate(l);
	AView::pushViewTemplates(l);
	return l;
}

static void			load_views_scripts(
	lua_State *l, std::vector<std::string> &scripts_paths)
{
	for (auto const &fname : scripts_paths)
	{
		if (luaL_dofile(l, fname.c_str()))
			throw std::runtime_error(
				ft::f("error loading '%': '%'"
					  , fname, luaL_checkstring(l, -1)));
	}
	scripts_paths.clear();
	scripts_paths.shrink_to_fit();
	return ;
}


void			Activity::pushActivity(void)
{
	ftlua::multiPush(
		_l, ftlua::make_keys("ftui"), "activity", ftlua::light(this));
	if (!lua_istable(_l, -3))
		throw std::runtime_error("Could not retrieve _G['ftui']");
	lua_settable(_l, -3);
	lua_pop(_l, 1);
	return ;
}

void			Activity::inflate(std::istream &stream)
{
	ft::XmlParser			xml(stream);
	AView					*v;
	ft::XmlParser::State	state;

	FTASSERT(_l == nullptr, "Activity.inflate called again");
	_l = new_lua_env();
	this->pushActivity();
	if (!xml.next(state))
		throw std::runtime_error("Activity should own at least 1 view");
	FTASSERT(state == ft::XmlParser::State::START, "Cannot fail");
	v = AView::getFactory(xml.getMarkupName())(*this, &xml, nullptr);
	this->_rootView = new Activity::RootViewHolder(*this, xml, v, this->_size);
	v->setViewHolder(this->_rootView);
	v->setAttached(true);
	v->inflate(*this, xml);
	if (xml.next(state))
		throw std::runtime_error("Activity should not own more than 1 view");
	load_views_scripts(_l, _scriptsPaths);
	FTASSERT(lua_gettop(_l) == 0, "Something went wrong...");
	return ;
}

void			Activity::saveScriptPath(std::string const &str)
{
	std::stringstream	ss(str);
	char				buf[64];

	// TODO accept folder as parameter
	while (ss.getline(buf, sizeof(buf), ';'))
		_scriptsPaths.push_back(buf);
	return ;
}

// ========================================================================== //
// LOOP TIME
//

void			Activity::render(Canvas &canvas)
{
	AView		*rv;

	if (!canvas.isInLua(_l))
		canvas.pushLua(_l);
	rv = this->_rootView == nullptr ? nullptr : this->_rootView->getView();
	if (rv == nullptr)
		return ;
	if (rv->isUpdateQueried())
	{
		rv->onUpdate();
	}
	if (rv->isMeasureQueried())
	{
		rv->onMeasure();
		_rootView->setSize(_size);
	}
	if (rv->isRedrawQueried())
	{
		canvas.clear(); //debug
		this->queryRedrawAll(); //debug
		// FTPADB("Redraw");
		rv->onDraw(canvas);
		// FTPADE();
	}
	return ;
}

// MOUSE / KEYBOARD INTERACTIONS ==== //
bool			Activity::onKeyUp(int key_code, int mods)
{
	if (_rootView != NULL && _rootView->getView()->isKeyboardTargeted())
		return (_rootView->getView()->onKeyUp(key_code, mods));
	return (false);
}

bool			Activity::onKeyDown(int key_code, int mods)
{
	if (_rootView != NULL && _rootView->getView()->isKeyboardTargeted())
		return (_rootView->getView()->onKeyDown(key_code, mods));
	return (false);
}

void			Activity::onMouseMove(int x, int y)
{
	auto		rv = _rootView != nullptr ? _rootView->getView() : nullptr;

	if (rv != nullptr && rv->isMouseMoveTargeted())
	{
		if (ft::Rect<int>{0, 0, _size.x, _size.y}.contains(ft::Vec2<int>{x, y}))
		{
			if (!rv->isMouseOver())
				rv->setMouseOver(x, y, true);
		}
		else
		{
			if (rv->isMouseOver())
				rv->setMouseOver(x, y, false);
		}
		if (rv->isMouseOver() || rv->isMouseCaptureTargeted())
		{
			rv->onMouseMove(x, y);
		}
	}
	return ;
}

void			Activity::onMouseUp(int x, int y, int button, int mods)
{
	auto	rv = _rootView != nullptr ? _rootView->getView() : nullptr;

	if (rv != nullptr)
	{
		if (rv->isMouseClickTargeted() &&
			(rv->isMouseOver() || rv->isMouseCaptureTargeted()))
		{
			rv->onMouseUp(x, y, button, mods);
		}
	}
	return ;
}

bool			Activity::onMouseDown(int x, int y, int button, int mods)
{
	auto	rv = _rootView != nullptr ? _rootView->getView() : nullptr;

	if (rv != nullptr)
	{
		if (rv->isMouseClickTargeted() &&
			(rv->isMouseOver() || rv->isMouseCaptureTargeted()))
		{
			return rv->onMouseDown(x, y, button, mods);
		}
	}
	return false;
}

//

void			Activity::queryRedrawAll(void)
{
	if (_rootView != NULL)
		_rootView->getView()->queryRedraw();
}

void			Activity::queryMeasureAll(void)
{
	if (_rootView != NULL)
		_rootView->getView()->queryMeasure();
}

void			Activity::queryUpdateAll(void)
{
	if (_rootView != NULL)
		_rootView->getView()->queryUpdate();
}

void			Activity::unregisterEvent(std::string const &event, AView *v)
{
	auto			it = this->_eventMap.find(event);
	auto const		ite = this->_eventMap.cend();

	while (it != ite)
	{
		if (it->second->getView() == v)
		{
			delete it->second;
			it = this->_eventMap.erase(it);
		}
		else
			it++;
	}
	return ;
}

void			Activity::registerLuaCFun_global(
	std::string const &funName, lua_CFunction f)
{
	lua_register(_l, funName.c_str(), f);
	return ;
}

void			Activity::registerLuaCFun_table(
	std::string const &tabName
	, std::string const &funName
	, lua_CFunction f)
{
	ftlua::registerLuaCFunTable(_l, tabName, funName, f);
	return ;
}

//

int				Activity::createViewG(lua_State *l)
{
	int const						top = lua_gettop(l);
	AView							*v;
	AView::view_info_s::factory_t	fact;
	std::string const				type(luaL_checkstring(l, 1));
	std::string	const *const		id = top == 2
		? (std::string[]){std::string(luaL_checkstring(l, 2))} : nullptr;

	if (top > 2)
		luaL_error(l, "Too many arguments");
	try {
		fact = AView::getFactory(type); }
	catch (...) {
		luaL_error(l, ft::f("Cannot find '%'", type).c_str()); }
	if (fact == nullptr)
		luaL_error(l, ft::f("Cannot instanciate '%'", type).c_str());
	lua_pop(l, top);
	v = fact(*Activity::retrieveActivity(l), nullptr, id);
	ftlua::push(l, v);
	FTASSERT(lua_istable(l, -1));
	return 1;
}

Activity		*Activity::retrieveActivity(lua_State *l)
{
	Activity	*act;

	ftlua::push(l, ftlua::make_keys("ftui", "activity"));
	if (!lua_islightuserdata(l, -1))
		luaL_error(l, "Could not retrieve activity pointer");
	act = reinterpret_cast<Activity*>(lua_touserdata(l, -1));
	lua_pop(l, 1);
	return act;
}

lua_State		*Activity::getLuaState(void) const
{
	return (_l);
}

AView			*Activity::getRoot(void)
{
	if (_rootView == NULL)
		return (NULL);
	return (_rootView->getView());
}

AView const		*Activity::getRoot(void) const
{
	if (_rootView == NULL)
		return (NULL);
	return (_rootView->getView());
}


};
