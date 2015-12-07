// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:27 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/07 15:46:22 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <algorithm>

#include "ft/utils.hpp"
#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/ACanvas.hpp"
#include "ft_xml/XmlParser.hpp"

extern "C"
{

#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

};

namespace ftui
{

#define WALK_DIR_MAX_DEPTH		16

// ========================================================================== //
// CONSTRUCTION
//

// CTOR / DTOR ====================== //
Activity::Activity(ft::Vec2<int> size) :
	_rootView(NULL),
	_eventMap(),
	_size(size),
	_l(nullptr),
	_cursorPos(0, 0)
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
		throw std::runtime_error("Activity::inflate: "
								 "Error while creating lua state");
	luaL_openlibs(l);
	err = luaL_dofile(l, (RES_PATH "/utils.lua"));
	FTASSERT(err == LUA_OK);
	ftlua::set(l, "createView", &Activity::createViewG);
	ftlua::pushUtils(l);
	ACanvas::pushTemplate(l);
	Activity::pushViewTemplates(l);
	return l;
}

static void			load_views_scripts(
	lua_State *l, std::vector<std::string> &scripts_paths)
{
	for (auto const &fname : scripts_paths)
	{
		if (luaL_dofile(l, fname.c_str()))
			throw std::runtime_error(
				ft::f("Activity::inflate: Error loading '%': '%'"
					  , fname, luaL_checkstring(l, -1)));
	}
	scripts_paths.clear();
	scripts_paths.shrink_to_fit();
	return ;
}

static bool		is_dir(char const *str)
{
	struct stat		s;

	if (stat(str, &s) == 0 && S_ISDIR(s.st_mode))
		return (true);
	return (false);
}

static void		walk_lua_dir(std::string const &dir_name,
					std::vector<std::string> &dst,
					int max_depth = WALK_DIR_MAX_DEPTH)
{
	DIR				*dir;
	struct dirent	*ent;
	std::string		ent_name;

	if ((dir = opendir(dir_name.c_str())) == NULL)
		return ;
	while ((ent = readdir(dir)) != NULL)
	{
		if (strcmp(ent->d_name, ".") == 0
			|| strcmp(ent->d_name, "..") == 0)
			continue ;
		ent_name = dir_name + "/" + ent->d_name;
		if (is_dir(ent_name.c_str()))
		{
			if (max_depth > 0)
				walk_lua_dir(ent_name, dst, max_depth - 1);
			continue ;
		}
		char const	*tmp = strrchr(ent->d_name, '.');
		if (tmp != NULL && strcmp(tmp, ".lua") == 0)
			dst.emplace_back(ent_name);
	}
	closedir(dir);
}

void			Activity::inflate(std::istream &stream)
{
	ft::XmlParser			xml(stream);
	AView					*rootView;
	ft::XmlParser::State	state;

	FTASSERT(_l == nullptr, "Activity.inflate called again");
	_l = new_lua_env();
	ftlua::set(_l, ftlua::makeKeys("ftui"), "activity", ftlua::light(this));
	while (xml.next(state))
	{
		if (state != ft::XmlParser::State::START)
			throw std::runtime_error("Activity::inflate: lol");
		if (xml.getMarkupName() != "template")
			break ;
		inflateTemplate(xml);
	}
	if (state != ft::XmlParser::State::START)
		throw std::runtime_error("Activity::inflate: "
								 "Activity should own 1 view");
	rootView = Activity::getFactory(xml.getMarkupName())(*this);
	this->_rootView = new Activity::RootViewHolder(*this, xml, rootView, this->_size);
	rootView->setViewHolder(this->_rootView);
	rootView->setAttached(true);
	rootView->inflate(xml);
	if (xml.next(state))
		throw std::runtime_error("Activity::inflate: "
								 "Activity should not own more than 1 view");
	load_views_scripts(_l, _scriptsPaths);
	FTASSERT(lua_gettop(_l) == 0, "Something went wrong...");
	return ;
}

void			Activity::inflateTemplate(std::istream &stream)
{
	ft::XmlParser			xml(stream);
	ft::XmlParser::State	state;

	while (xml.next(state))
	{
		if (state != ft::XmlParser::State::START)
			throw std::runtime_error("Activity::inflate: Unexpected token");
		if (xml.getMarkupName() != "template")
			throw std::domain_error(ft::f("Activity::inflate: "
				"Not a template: %", xml.getMarkupName()));
		inflateTemplate(xml);
	}
}

void			Activity::inflateTemplate(ft::XmlParser &xml)
{
	ViewTemplate		*viewTemplate = new ViewTemplate(xml);
	auto const &params = viewTemplate->getParams();
	auto const &it = std::find_if(params.begin(), params.end(),
		[](auto const &param)
		{
			return (param.first == "name");
		});
	if (it == params.end())
		throw std::runtime_error("Activity::inflate: "
								"<template> without 'name' param");
	if (!_viewTemplates.insert({it->second, viewTemplate}).second)
		throw std::runtime_error(ft::f("Activity::inflate: "
				"Template redefinition: %", it->second));
}

void			Activity::saveScriptPath(std::string const &str)
{
	std::stringstream	ss(str);
	char				buf[64];

	while (ss.getline(buf, sizeof(buf), ';'))
	{
		if (is_dir(buf))
			walk_lua_dir(buf, _scriptsPaths);
		else
			_scriptsPaths.push_back(buf);
	}
	return ;
}

/*
** ========================================================================== **
** View template
*/

ViewTemplate const	*Activity::getViewTemplate(std::string const &name) const
{
	auto const		&it = _viewTemplates.find(name);

	if (it == _viewTemplates.end())
		return (nullptr);
	return (it->second);
}

// ========================================================================== //
// LOOP TIME
//

void			Activity::render(ACanvas &canvas)
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
		canvas.clear(); //TODO debug
		this->queryRedrawAll(); //TODO debug
		// FTPADB("Redraw");
		canvas.setOrigin(ft::make_vec(0, 0));
		canvas.setClip(_size);
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

void			Activity::onMouseScroll(float delta)
{
	auto		rv = _rootView != nullptr ? _rootView->getView() : nullptr;

	if (rv != nullptr && ((rv->isMouseScrollTargeted()
				&& ft::Rect<int>{0, 0, _size.x, _size.y}.contains(_cursorPos))
			|| rv->isMouseCaptureTargeted()))
		rv->onMouseScroll(_cursorPos.x, _cursorPos.y, delta);
}

void			Activity::onMouseMove(int x, int y)
{
	auto		rv = _rootView != nullptr ? _rootView->getView() : nullptr;

	_cursorPos.x = x;
	_cursorPos.y = y;
	if (rv != nullptr && rv->isMouseMoveTargeted())
	{
		if ((ft::make_vec(0, 0) ^ _size).contains(ft::make_vec(x, y)))
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

void			Activity::registerEvent(std::string const &event, AView *v)
{
	this->_eventMap.insert(std::make_pair(event, new EventTarget(v)));
	return ;
}

void			Activity::removeFromEvents(
	std::pair<std::string, AView*> const &p)
{
	auto			it = this->_eventMap.find(p.first);
	auto const		ite = this->_eventMap.cend();

	while (it != ite)
	{
		if (it->second->getView() == p.second)
		{
			delete it->second;
			it = this->_eventMap.erase(it);
		}
		else
			it++;
	}
	return ;
}

void			Activity::cleanEventMap(void)
{
	while (!this->_unregisterStack.empty())
	{
		removeFromEvents(this->_unregisterStack.top());
		this->_unregisterStack.pop();
	}
	return ;
}
void			Activity::unregisterEvent(std::string const &event, AView *v)
{
	this->_unregisterStack.push({event, v});
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
	ftlua::set(_l, ftlua::makeKeys(tabName), funName, f);
	return ;
}

//

int				Activity::createViewG(lua_State *l)
{
	int const					top = lua_gettop(l);
	AView						*v;
	Activity::view_factory_t	fact;
	std::string const			type(luaL_checkstring(l, 1));

	FTLUA_STACKASSERT(l, top <= 1, true, "Activity::createViewG"
					  , "Too many arguments");
	try {
		fact = Activity::getFactory(type); }
	catch (...) {
		luaL_error(l, ft::f("Activity::createViewG: "
							"Cannot find type '%'", type).c_str()); }
	if (fact == nullptr)
		luaL_error(l, ft::f("Activity::createViewG: "
							"Cannot instanciate type '%'", type).c_str());
	lua_pop(l, top);
	v = fact(*Activity::retrieveActivity(l));
	ftlua::push(l, v);
	FTASSERT(lua_istable(l, -1));
	return 1;
}

Activity		*Activity::retrieveActivity(lua_State *l)
{
	Activity	*act;

	ftlua::push(l, ftlua::makeKeys("ftui", "activity"));
	FTLUA_STACKASSERT(l, lua_islightuserdata(l, -1), true
					  , "Activity::retrieveActivity"
					  , "Could not retrieve _G['ftui']['activity']");
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
