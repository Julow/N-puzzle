// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:27 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/09 14:00:58 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <algorithm>
#include <iostream> //debug

#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/XmlParser.hpp"

namespace ftui
{

Activity::Activity(ft::Vec2<int> size) :
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

static void		finalize_table(
	lua_State *l, std::string const &name, AView::view_info_s const &i)
{
	(void)lua_getglobal(l, name.c_str());
	if (i.parent != "" )
	{
		if (lua_getglobal(l, i.parent.c_str()) != LUA_TTABLE)
			;//TODO throw
		lua_setmetatable(l, -2);
	}
	lua_pushstring(l, "__index");
	lua_pushvalue(l, -2);
	lua_settable(l, -3);
	// lua_pushstring(l, "__newindex");
	// lua_pushstring(l, "no way");
	// lua_settable(l, -3);
	// lua_pushstring(l, "__metatable");
	// lua_pushstring(l, "not your business");
	// lua_settable(l, -3);
	lua_setglobal(l, name.c_str());
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
	ftui::lua_pushUtils(*this);
	for (auto it : AView::viewsInfo)
	{
		lua_createtable(_l, 0, 0);
		lua_setglobal(_l, it.first.c_str());
	}
	for (auto it : AView::viewsInfo)
	{
		for (auto itm : it.second.luaMethods)
			this->registerLuaCFun_table(
				it.first, std::get<0>(itm), std::get<1>(itm));
	}
	for (auto it : AView::viewsInfo)
		finalize_table(_l, it.first, it.second);
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

lua_State		*Activity::getLuaState(void) const
{
	return _l;
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
		_rootView->setSize(_rootView->getRequestedSize());
	}
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
	, std::string const &funName, lua_CFunction f)
{
	int		t;

	t = lua_getglobal(_l, tabName.c_str());
	if (t != LUA_TTABLE)
		; //TODO throw
	lua_pushstring(_l, funName.c_str());
	lua_pushcfunction(_l, f);
	lua_settable(_l, -3);
	lua_setglobal(_l, tabName.c_str());
	return ;
}

};
