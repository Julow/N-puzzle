// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:27 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/08 10:12:07 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <algorithm>
#include <iostream>

#include "ft/utils.hpp"
#include "ftlua/ftlua.hpp"
#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/XmlParser.hpp"

namespace ftui
{

/*
** ************************************************************************** **
** Init-time / End-time -> instance.CTOR / instance.DTOR
*/

Activity::Activity(ft::Vec2<int> size) :
	_rootView(NULL),
	_eventMap(),
	_size(size),
	_l(nullptr)
{
	std::cout << "Activity CTOR" << std::endl;
	return ;
}

Activity::~Activity(void)
{
	if (_l != nullptr)
		lua_close(_l);
	// TODO: release views
	return ;
}

/*
** ************************************************************************** **
** Init-time -> instance.inflate
*/

static void		init_template_table(
	lua_State *l
	, std::string const &view_name
	, std::string const &tableinit_luacode)
{
	if (luaL_dostring(l, tableinit_luacode.c_str()) != LUA_OK)
		throw std::runtime_error(ft::f("Cannot init table '%'", view_name));
	if (lua_getglobal(l, view_name.c_str()) != LUA_TTABLE)
	{
		lua_createtable(l, 0, 0);
		lua_setglobal(l, view_name.c_str());
	}
	lua_pop(l, 1);
	return ;
}

static void		push_luacfun_methods(
	lua_State *l
	, std::string const &view_name
	, std::vector<AView::view_info_s::luamethod_t> const &methods)
{
	for (auto itm : methods)
		ftlua::registerLuaCFunTable(
			l, view_name, std::get<0>(itm), std::get<1>(itm));
	return ;
}

static void		finalize_template(
	lua_State *l, std::string const &name, AView::view_info_s const &i)
{
	int		err;

	err = 0;
	(void)lua_getglobal(l, "ft");
	lua_pushstring(l, "finalize_template");
	(void)lua_gettable(l, -2);
	(void)lua_getglobal(l, name.c_str());
	(void)lua_getglobal(l, i.parent.c_str());
	err |= lua_pcall(l, 2, 0, 0);
	FTASSERT(err == 0);
	lua_pop(l, 1);
	return ;
}

static void		push_view_templates(lua_State *l)
{
	for (auto const &it : AView::viewsInfo)
		init_template_table(l, it.first, it.second.tableInit);
	for (auto const &it : AView::viewsInfo)
		push_luacfun_methods(l, it.first, it.second.luaMethods);
	for (auto const &it : AView::viewsInfo)
		finalize_template(l, it.first, it.second);
	return ;
}

static lua_State	*new_lua_env(void)
{
	lua_State *const	l = luaL_newstate();

	if (l == nullptr)
		throw std::runtime_error("Error while creating lua state");
	luaL_openlibs(l);
	// TODO: rpath in binary to write utils in .lua file
	ftlua::pushUtils(l);
	push_view_templates(l);
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

void			Activity::inflate(std::istream &stream)
{
	XmlParser			xml(stream);
	AView				*v;
	XmlParser::State	state;

	FTASSERT(_l == nullptr, "Activity.inflate called again");
	_l = new_lua_env();
	if (!xml.next(state))
		throw std::runtime_error("Activity should own at least 1 view");
	FTASSERT(state == XmlParser::State::START, "Cannot fail");
	v = AView::getFactory(xml.getMarkupName())(xml, *this);
	this->_rootView = new Activity::RootViewHolder(xml, v, this->_size);
	v->inflate(xml, *this);
	v->setViewHolder(this->_rootView);
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

/*
** ************************************************************************** **
** Render-time -> internal functions
*/

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

/*
** ************************************************************************** **
** Render-time -> instance.render
*/

void			Activity::render(Canvas &canvas)
{
	AView		*rv;

	rv = this->_rootView == nullptr ? nullptr : this->_rootView->getView();
	if (rv == nullptr)
		return ;
	if (rv->isUpdateQueried())
		rv->onUpdate();
	if (rv->isMeasureQueried())
	{
		rv->onMeasure();
		_rootView->setSize(_size);
	}
	if (rv->isRedrawQueried())
	{
		std::cout << "REDRAW REQ" << std::endl;
		rv->onDraw(canvas);
	}
	return ;
}

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

/*
** ************************************************************************** **
** Render-time -> key/mouse entry point 'window event'->'activity event'
*/

bool			Activity::onKeyUp(int key_code)
{
	if (_rootView != NULL && _rootView->getView()->isKeyboardTargeted())
		return (_rootView->getView()->onKeyUp(key_code));
	return (false);
}

bool			Activity::onKeyDown(int key_code)
{
	if (_rootView != NULL && _rootView->getView()->isKeyboardTargeted())
		return (_rootView->getView()->onKeyDown(key_code));
	return (false);
}

/*
** ************************************************************************** **
** Render-time -> instance.*Event		(more in Activity.tpp)
*/

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

/*
** ************************************************************************** **
** Render-time -> register 'c' function for 'lua->c' callback
*/

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

};
