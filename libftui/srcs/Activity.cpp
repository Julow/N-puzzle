/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:27 by jaguillo          #+#    #+#             */
//   Updated: 2015/10/04 15:07:31 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream> //debug

#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/XmlParser.hpp"

namespace ftui
{

Activity::Activity(Vec2<int> size) :
	_rootView(NULL),
	_eventMap(),
	_size(size),
	_l(nullptr)
{
	this->_l = luaL_newstate();
	if (_l == nullptr)
		;//TODO throw
	luaL_openlibs(_l);
	return ;
}

Activity::~Activity(void)
{
	if (_l != nullptr)
		lua_close(_l);
	return ;
}

void			Activity::init_lua_env(void)
{
	if (_l != nullptr)
		;//TODO ?
	this->_l = luaL_newstate();
	if (_l == nullptr)
		;//TODO throw
	luaL_openlibs(_l);
	// ftlua::pushUtils();
	for (auto it : AView::viewsInfo)
	{
		std::cout << "Created lua table" << it.first << std::endl;
		lua_createtable(_l, 0, 0);
		lua_setglobal(_l, it.first.c_str());
	}
	for (auto it : AView::viewsInfo)
		this->registerMemfuns(it.first, it.second.luaMemfuns);
	for (auto it : AView::viewsInfo)
	{
		std::cout << "Applying inheritance for '" << it.first << "' to '"
				  << it.second.parent << "'" << std::endl;
		(void)lua_getglobal(_l, it.first.c_str());
		if (it.second.parent != "" )
		{
			if (lua_getglobal(_l, it.second.parent.c_str()) != LUA_TTABLE)
				;//TODO throw
			lua_setmetatable(_l, -2);
		}
		// uncomment to protect the table
		// lua_pushstring(_l, "__newindex");
		// lua_pushvalue(_l, -2);
		// lua_settable(_l, -3);
		// lua_pushstring(_l, "__metatable");
		// lua_pushstring(_l, "not your business");
		// lua_settable(_l, -3);
		lua_setglobal(_l, it.first.c_str());
	}
	return ;
}

void			Activity::inflate(std::istream &stream)
{
	XmlParser			xml(stream);
	AView				*v;
	XmlParser::State	state;

	if (_l == nullptr)
		;//TODO ?
	this->init_lua_env();// TODO, move elsewhere
	if (!xml.next(state))
		FTASSERT(false, "Activity should own at least 1 view");
	FTASSERT(state == XmlParser::State::START, "Cannot fail");
	v = AView::getFactory(xml.getMarkupName())(xml, *this);
	this->_rootView = new Activity::RootViewHolder(xml, v, this->_size);
	v->inflate(xml, *this);
	v->setViewHolder(this->_rootView);
	if (xml.next(state))
		FTASSERT(false, "Activity should not own more than 1 view");
	return ;
}

void			Activity::render(ACanvas &canvas)
{
	AView		*rv;

	rv = this->_rootView == nullptr ? nullptr : this->_rootView->getView();
	if (rv == nullptr)
		return ;
	if (rv->isUpdateQueried())
		rv->onUpdate();
	if (rv->isMeasureQueried())
		rv->onMeasure();
	if (rv->isRedrawQueried())
		rv->onDraw(canvas);
	return ;
}

void			Activity::unregisterEvent(std::string const &event, AView *v)
{
	auto                    it = this->_eventMap.find(event);
	auto const              ite = this->_eventMap.cend();

	while (it != ite)
	{
		if (it->second->getView() == v)
			it = this->_eventMap.erase(it);
		else
			it++;
	}
	return ;
}

void			Activity::registerGFun(
	std::string const &funName, lua_CFunction f)
{
	lua_register(_l, funName.c_str(), f);
	return ;
}

void			Activity::registerMemfuns(
	std::string const &tabName
	, std::vector<std::tuple<std::string, lua_CFunction>> const &fns)
{
	int		t;

	t = lua_getglobal(_l, tabName.c_str());
	std::cout << "Registering memfuncs for " << tabName << std::endl;
	if (t != LUA_TTABLE)
		; //TODO throw
	for (auto it : fns)
	{
		lua_pushstring(_l, std::get<0>(it).c_str());
		lua_pushcfunction(_l, std::get<1>(it));
		lua_settable(_l, -3);
		std::cout << "    Registered lua function self:"
				  << std::get<0>(it) << std::endl;
	}
	lua_setglobal(_l, tabName.c_str());
	return ;
}

};
