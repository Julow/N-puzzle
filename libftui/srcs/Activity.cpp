// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:27 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/10 13:51:12 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <algorithm>

#include "ft/utils.hpp"
#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/XmlParser.hpp"

namespace ftui
{

/*
** TODO: Allow to call AView::defineView after Activity constructor
*/
Activity::Activity(ft::Vec2<int> size) :
	_rootView(NULL),
	_eventMap(),
	_size(size),
	_l(nullptr)
{
	init_lua_env();
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
	(void)lua_getglobal(l, "finalize_template");
	(void)lua_getglobal(l, name.c_str());
	(void)lua_getglobal(l, i.parent.c_str());
	lua_call(l, 2, 0);	
	return ;
}

static void	load_special_code(lua_State *l)
{
	// TODO move this lua function to C or to new htab
	luaL_dostring(l, "ALayout.__ipairs = function(t)       \
	 local i, n = -1, t:size()                             \
	 print('__pairs for ', t, n);						   \
	 return function()                                     \
	         i = i + 1                                     \
	         if i < n then                                 \
	             return i, t:at(i);						   \
	         end										   \
	     end											   \
	 end");
	luaL_dostring(l, "finalize_template = function(t, p)	\
		t.__index = t;										\
		if p ~= nil then									\
			setmetatable(t, p);								\
			if t.__ipairs == nil then						\
				t.__ipairs = p.__ipairs						\
			end												\
		end													\
	end");
	return ;
}

static void	unload_special_code(lua_State *l)
{
	luaL_dostring(l, "finalize_template = nil;");
	return ;
}


void			Activity::init_lua_env(void)
{
	FTASSERT(_l == nullptr, "lua state already created");
	this->_l = luaL_newstate();
	if (_l == nullptr)
		throw std::runtime_error("Error while creating lua state");
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
	load_special_code(_l);
	for (auto it : AView::viewsInfo)
		finalize_table(_l, it.first, it.second);
	unload_special_code(_l);
	return ;
}

void			Activity::inflate(std::istream &stream)
{
	XmlParser			xml(stream);
	AView				*v;
	XmlParser::State	state;

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
		throw std::runtime_error(ft::f("Lua: Corrupted table (%)", tabName));
	lua_pushstring(_l, funName.c_str());
	lua_pushcfunction(_l, f);
	lua_settable(_l, -3);
	lua_setglobal(_l, tabName.c_str());
	return ;
}

};
