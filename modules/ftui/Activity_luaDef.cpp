// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity_luaDef.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/25 18:03:11 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/01 19:34:03 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <tuple>

#include "ft/utils.hpp"
#include "ftui/AView.hpp"
#include "ftui/ALayout.hpp"
#include "ftui/LinearLayout.hpp"
#include "ftui/SolidView.hpp"
#include "ftui/SliderView.hpp"
#include "ftui/ScrollableLayout.hpp"
#include "ftui/ASolidView.hpp"
#include "ftui/TextView.hpp"
#include "ftui/Button.hpp"
#include "ftui/CheckBox.hpp"

namespace ftui
{

#define INSG(T, N) std::make_tuple(#N, &T::N##G)
#define INSG_AV(N) INSG(AView, N)

Activity::views_info_t		Activity::viewsInfo
{
	{"AView", {"", nullptr, {
		INSG_AV(setRequestedSize), INSG_AV(setAlpha), INSG_AV(setVisibility),
		INSG_AV(setParam), INSG_AV(hookMouseScroll), INSG_AV(hookMouseClick),
		INSG_AV(hookMouseMove), INSG_AV(hookMouseCapture),
		INSG_AV(hookKeyboard), INSG_AV(queryUpdate), INSG_AV(queryMeasure),
		INSG_AV(queryRedraw), INSG_AV(getRequestedSize), INSG_AV(getPos),
		INSG_AV(getSize), INSG_AV(getId), INSG_AV(getParent), INSG_AV(getAlpha),
		INSG_AV(isVisible), INSG_AV(isMouseOver),
		INSG_AV(isMouseScrollTargeted), INSG_AV(isMouseClickTargeted),
		INSG_AV(isMouseCaptureTargeted), INSG_AV(isKeyboardTargeted),
		INSG_AV(isUpdateQueried), INSG_AV(isMeasureQueried),
		INSG_AV(isRedrawQueried), INSG_AV(setCallback), INSG_AV(registerEvent),
		INSG_AV(unregisterEvent), INSG_AV(setId)
	}, {}}},
	{"ASolidView", {"AView", nullptr, {
		INSG(ASolidView, getBackgroundColor), INSG(ASolidView, getBorderColor),
		INSG(ASolidView, getBorderWidth), INSG(ASolidView, setBackgroundColor),
		INSG(ASolidView, setBorderColor), INSG(ASolidView, setBorderWidth),
	}, {}}},
	{"TextView", {"ASolidView", &TextView::createView, {
		INSG(TextView, getText), INSG(TextView, setText),
		INSG(TextView, getFont), INSG(TextView, setFont),
		INSG(TextView, getTextColor), INSG(TextView, setTextColor),
		INSG(TextView, getTextSize), INSG(TextView, setTextSize),
	}, {}}},
	{"SliderView", {"ASolidView", &SliderView::createView, {
		INSG(SliderView, getValue), INSG(SliderView, setValue),
		INSG(SliderView, getStepValue), INSG(SliderView, setStepValue),
		INSG(SliderView, getBounds), INSG(SliderView, setBounds),
		INSG(SliderView, getSteps), INSG(SliderView, setSteps),
	}, {}}},
	{"Button", {"ASolidView", &Button::createView, {
		INSG(Button, lockHighlight), INSG(Button, setNormalParams),
		INSG(Button, setDisabledParams), INSG(Button, setPushedParams),
		INSG(Button, setHighlightParams),
	}, {}}},
	{"CheckBox", {"Button", &CheckBox::createView, {
		INSG(CheckBox, setCheckedParams), INSG(CheckBox, setDisabledCheckedParams),
		INSG(CheckBox, isChecked), INSG(CheckBox, setChecked),
	}, {}}},
	{"ALayout", {"ASolidView", nullptr, {
		INSG(ALayout, size), INSG(ALayout, at), INSG(ALayout, addView)
	}, "ALayout = ftui.ALayoutdef; ftui.ALayoutdef = nil;"}},
	{"LinearLayout", {"ALayout", &LinearLayout::createView, {
		INSG(LinearLayout, getDirection), INSG(LinearLayout, setDirection),
	}, {}}},
	{"ScrollableLayout", {"LinearLayout", &ScrollableLayout::createView, {
		INSG(ScrollableLayout, getScroll), INSG(ScrollableLayout, setScroll),
		INSG(ScrollableLayout, getMaxScroll),
	}, {}}},
	{"SolidView", {"ASolidView", &SolidView::createView, {}, {}}},
};

#define LUA_CALLBACK_ID(V,NAME)	static_cast<uint32_t>(V::LuaCallback::NAME)

Activity::callback_map_t	Activity::callback_map
{
	{"onMouseScroll",		LUA_CALLBACK_ID(AView, MOUSE_SCROLL)},
	{"onUpdate",			LUA_CALLBACK_ID(AView, UPDATE)},
	{"onMeasure",			LUA_CALLBACK_ID(AView, MEASURE)},
	{"onDraw",				LUA_CALLBACK_ID(AView, DRAW)},
	{"onMouseScroll",		LUA_CALLBACK_ID(AView, MOUSE_SCROLL)},
	{"onMouseDown",			LUA_CALLBACK_ID(AView, MOUSE_DOWN)},
	{"onMouseUp",			LUA_CALLBACK_ID(AView, MOUSE_UP)},
	{"onMouseMove",			LUA_CALLBACK_ID(AView, MOUSE_MOVE)},
	{"onKeyDown",			LUA_CALLBACK_ID(AView, KEY_DOWN)},
	{"onKeyUp",				LUA_CALLBACK_ID(AView, KEY_UP)},
	{"onMouseEnter",		LUA_CALLBACK_ID(AView, MOUSE_ENTER)},
	{"onMouseLeave",		LUA_CALLBACK_ID(AView, MOUSE_LEAVE)},
	{"onEvent",				LUA_CALLBACK_ID(AView, EVENT)},
	{"onPositionChange",	LUA_CALLBACK_ID(AView, POSITION_CHANGE)},
	{"onCaptureChange",		LUA_CALLBACK_ID(AView, CAPTURE_CHANGE)},
	{"onSizeChange",		LUA_CALLBACK_ID(AView, SIZE_CHANGE)},
	{"onVisibilityChange",	LUA_CALLBACK_ID(AView, VISIBILITY_CHANGE)},
	{"onAttach",			LUA_CALLBACK_ID(AView, ATTACH)},
	{"onDetach",			LUA_CALLBACK_ID(AView, ATTACH)},

	{"onClick",				LUA_CALLBACK_ID(Button, CLICK)},
	{"onDoubleClick",		LUA_CALLBACK_ID(Button, DOUBLE_CLICK)},

	{"onValueChange",		LUA_CALLBACK_ID(SliderView, VALUE_CHANGE)},

	{"onScrollChange",		LUA_CALLBACK_ID(ScrollableLayout, SCROLL_CHANGE)},
	{"onMaxScrollChange",	LUA_CALLBACK_ID(ScrollableLayout, MAX_SCROLL_CHANGE)},
};

Activity::view_factory_t	Activity::getFactory(std::string const &name)
{
	view_info_s			f;

	f = Activity::viewsInfo.at(name);
	return (f.factory);
}

void				Activity::defineClass(
	std::string const &name,
	std::string const &parent,
	Activity::view_factory_t factory,
	std::vector<view_info_s::luamethod_t> luaMethods /* = ...*/,
	std::string const &tableInit /* = ...*/)
{
	if (!Activity::viewsInfo.insert(std::make_pair(name,
			Activity::view_info_s{parent, factory, luaMethods, tableInit})).second)
		throw std::domain_error(ft::f("Activity::defineClass: "
									  "View % already defined", name));
	return ;
}

void			Activity::registerLuaCallback(std::string const &name, uint32_t id)
{
	if (!callback_map.insert(std::make_pair(name, id)).second)
		throw std::domain_error(ft::f("Activity::registerLuaCallback: "
									  "Lua callback registered twice (%)",
			name));
}

static void     init_template_table(
	    lua_State *l
		, std::string const &view_name
		, std::string const &tableinit_luacode)
{
	if (luaL_dostring(l, tableinit_luacode.c_str()) != LUA_OK)
		throw std::runtime_error(ft::f("Activity::inflate: "
									   "Cannot init lua table '%'", view_name));
	if (lua_getglobal(l, view_name.c_str()) != LUA_TTABLE)
		ftlua::set(l, view_name, ftlua::newtab);
	lua_pop(l, 1);
	return ;
}

static void     push_luacfun_methods(
	    lua_State *l
		, std::string const &view_name
		, std::vector<Activity::view_info_s::luamethod_t> const &methods)
{
	for (auto const &itm : methods)
		ftlua::set(l, ftlua::makeKeys(view_name)
				   , std::get<0>(itm), std::get<1>(itm));
	return ;
}

static void     finalize_template(
	lua_State *l, std::string const &name, Activity::view_info_s const &i)
{
	int     err;

	ftlua::push(l, ftlua::makeKeys("ftui", "finalize_template"));
	err = ftlua::pcall(
		l, 0, 0, ftlua::makeKeys(name), ftlua::makeKeys(i.parent));
	FTASSERT(err == 0);
	return ;
}

void			Activity::pushViewTemplates(lua_State *l)
{
	for (auto const &it : Activity::viewsInfo)
		init_template_table(l, it.first, it.second.tableInit);
	for (auto const &it : Activity::viewsInfo)
		push_luacfun_methods(l, it.first, it.second.luaMethods);
	for (auto const &it : Activity::viewsInfo)
		finalize_template(l, it.first, it.second);
	return ;
}

};
