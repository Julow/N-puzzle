// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_statics.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:15 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/07 11:57:50 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

#include "ft/utils.hpp"
#include "ftui/AView.hpp"
#include "ftui/ALayout.hpp"
#include "ftui/VerticalLayout.hpp"
#include "ftui/SolidView.hpp"
#include "ftui/ASolidView.hpp"
#include "ftui/TextView.hpp"

namespace ftui
{

#define INSG(T, N) std::make_tuple(#N, &T::N##G)
#define INSG_AV(N) INSG(AView, N)

AView::views_info_t				AView::viewsInfo
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
		INSG_AV(isRedrawQueried), INSG_AV(setCallback),
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
	{"ALayout", {"ASolidView", nullptr, {
		INSG(ALayout, size), INSG(ALayout, at)
	}, "\
		ALayout = {											\
			__ipairs = function(t)							\
				local i, n = -1, t:size();					\
															\
				return function()							\
					i = i + 1;								\
					if i < n then							\
						return i, t:at(i);					\
					end										\
				end											\
			end												\
		}"}},
	{"VerticalLayout", {"ALayout", &VerticalLayout::createView, {}, {}}},
	{"SolidView", {"ASolidView", &SolidView::createView, {}, {}}},
};

#define LUA_CALLBACK_ID(NAME)	static_cast<uint32_t>(AView::LuaCallback::NAME)

AView::callback_map_t	AView::callback_map
{
	{"onMouseScroll",		LUA_CALLBACK_ID(MOUSE_SCROLL)},
	{"onUpdate",			LUA_CALLBACK_ID(UPDATE)},
	{"onMeasure",			LUA_CALLBACK_ID(MEASURE)},
	{"onDraw",				LUA_CALLBACK_ID(DRAW)},
	{"onMouseScroll",		LUA_CALLBACK_ID(MOUSE_SCROLL)},
	{"onMouseDown",			LUA_CALLBACK_ID(MOUSE_DOWN)},
	{"onMouseUp",			LUA_CALLBACK_ID(MOUSE_UP)},
	{"onMouseMove",			LUA_CALLBACK_ID(MOUSE_MOVE)},
	{"onKeyDown",			LUA_CALLBACK_ID(KEY_DOWN)},
	{"onKeyUp",				LUA_CALLBACK_ID(KEY_UP)},
	{"onMouseEnter",		LUA_CALLBACK_ID(MOUSE_ENTER)},
	{"onMouseLeave",		LUA_CALLBACK_ID(MOUSE_LEAVE)},
	{"onEvent",				LUA_CALLBACK_ID(EVENT)},
	{"onPositionChange",	LUA_CALLBACK_ID(POSITION_CHANGE)},
	{"onCaptureChange",		LUA_CALLBACK_ID(CAPTURE_CHANGE)},
	{"onSizeChange",		LUA_CALLBACK_ID(SIZE_CHANGE)},
	{"onVisibilityChange",	LUA_CALLBACK_ID(VISIBILITY_CHANGE)},
};

AView::view_info_s::factory_t	AView::getFactory(std::string const &name)
{
	AView::view_info_s		f;

	f = AView::viewsInfo.at(name);
	return (f.factory);
}

void				AView::defineView(
	std::string const &name,
	std::string const &parent,
	view_info_s::factory_t factory,
	std::vector<view_info_s::luamethod_t> luaMethods /* = ...*/,
	std::string const &tableInit /* = ...*/)
{
	if (!AView::viewsInfo.insert(std::make_pair(name,
			AView::view_info_s{parent, factory, luaMethods, tableInit})).second)
		throw std::domain_error(ft::f("View % already defined", name));
	return ;
}

void			AView::registerLuaCallback(std::string const &name, uint32_t id)
{
	if (callback_map.insert(std::make_pair(name, id)).second)
		throw std::domain_error(ft::f("lua callback registered twice (%)",
			name));
}

};
