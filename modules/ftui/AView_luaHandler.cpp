// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_luaHandler.cpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:25 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/01 16:59:56 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/AView.hpp"
#include "ftui/ALayout.hpp" // Do not remove, gives info about cast operator
#include "ftui/IViewHolder.hpp"
#include "ftui/ASolidView.hpp"
#include "ftui/TextView.hpp"

namespace ftui
{

#define DEF_LUACFUN_GSUFFIX(CLASS, NAME, NUMIN, NUMOUT)			\
int			CLASS::NAME##G(lua_State *l)						\
{																\
	return ftlua::handle<NUMIN, NUMOUT>(l, &CLASS::NAME);		\
}

#define DEF_LUACFUN_G_CAST(CLASS, NAME, NUMIN, NUMOUT, RET, ...)		\
int			CLASS::NAME##G(lua_State *l)								\
{																		\
	return ftlua::handle<NUMIN, NUMOUT>(l,								\
		reinterpret_cast<RET (CLASS::*)(__VA_ARGS__)>(&CLASS::NAME));	\
}

/*
** TextView
*/

DEF_LUACFUN_GSUFFIX(TextView, setText,				2, 0)
DEF_LUACFUN_GSUFFIX(TextView, getFont,				1, 1)
DEF_LUACFUN_GSUFFIX(TextView, setFont,				2, 0)
DEF_LUACFUN_GSUFFIX(TextView, getTextColor,			1, 1)
DEF_LUACFUN_GSUFFIX(TextView, setTextColor,			2, 0)
DEF_LUACFUN_GSUFFIX(TextView, getTextSize,			1, 1)
DEF_LUACFUN_GSUFFIX(TextView, setTextSize,			2, 0)

int			TextView::getTextG(lua_State *l)
{
	TextView *const				i = ftlua::retrieveSelf<TextView>(l, -1);

	return ftlua::push(l, i->getText());
}

/*
** ASolidView
*/

DEF_LUACFUN_GSUFFIX(ASolidView, getBorderWidth,		1,	1)
DEF_LUACFUN_GSUFFIX(ASolidView, setBorderWidth,		2,	0)
DEF_LUACFUN_GSUFFIX(ASolidView, getBackgroundColor,	1,	1)
DEF_LUACFUN_GSUFFIX(ASolidView, getBorderColor,		1,	1)
DEF_LUACFUN_GSUFFIX(ASolidView, setBackgroundColor,	2,	0)
DEF_LUACFUN_GSUFFIX(ASolidView, setBorderColor,		2,	0)

/*
** AView
*/

DEF_LUACFUN_GSUFFIX(AView, setAlpha,				2,	0)
DEF_LUACFUN_GSUFFIX(AView, setVisibility,			2,	0)
DEF_LUACFUN_GSUFFIX(AView, setParam,				3,	0)
DEF_LUACFUN_GSUFFIX(AView, hookMouseScroll,			2,	0)
DEF_LUACFUN_GSUFFIX(AView, hookMouseClick,			2,	0)
DEF_LUACFUN_GSUFFIX(AView, hookMouseMove,			2,	0)
DEF_LUACFUN_GSUFFIX(AView, hookMouseCapture,		2,	0)
DEF_LUACFUN_GSUFFIX(AView, hookKeyboard,			2,	0)
DEF_LUACFUN_GSUFFIX(AView, queryUpdate,				1,	0)
DEF_LUACFUN_GSUFFIX(AView, queryMeasure,			1,	0)
DEF_LUACFUN_GSUFFIX(AView, queryRedraw,				1,	0)
DEF_LUACFUN_GSUFFIX(AView, getAlpha,				1,	1)
DEF_LUACFUN_GSUFFIX(AView, isVisible,				1,	1)
DEF_LUACFUN_GSUFFIX(AView, isMouseOver,				1,	1)
DEF_LUACFUN_GSUFFIX(AView, isMouseScrollTargeted,	1,	1)
DEF_LUACFUN_GSUFFIX(AView, isMouseClickTargeted,	1,	1)
DEF_LUACFUN_GSUFFIX(AView, isMouseCaptureTargeted,	1,	1)
DEF_LUACFUN_GSUFFIX(AView, isKeyboardTargeted,		1,	1)
DEF_LUACFUN_GSUFFIX(AView, isUpdateQueried,			1,	1)
DEF_LUACFUN_GSUFFIX(AView, isMeasureQueried,		1,	1)
DEF_LUACFUN_GSUFFIX(AView, isRedrawQueried,			1,	1)
DEF_LUACFUN_GSUFFIX(AView, getParent,				1,	1)

DEF_LUACFUN_GSUFFIX(AView, registerEvent,			2,	0)
DEF_LUACFUN_GSUFFIX(AView, unregisterEvent,			2,	0)


int			AView::setCallbackG(lua_State *l)
{
	AView *const		i = ftlua::retrieveSelf<AView>(l, -3, false);

	i->setLuaCallback(l);
	return (0);
}

DEF_LUACFUN_GSUFFIX(AView, getId,					1,	1)


int			AView::getRequestedSizeG(lua_State *l)
{
	IViewHolder *const	h = ftlua::retrieveSelf<AView>(l, -1)->getViewHolder();

	return ftlua::push(l, h->getRequestedSize());
}

int			AView::getPosG(lua_State *l)
{
	IViewHolder *const	h = ftlua::retrieveSelf<AView>(l, -1)->getViewHolder();

	return ftlua::push(l, h->getPos());
}

int			AView::getSizeG(lua_State *l)
{
	IViewHolder *const	h = ftlua::retrieveSelf<AView>(l, -1)->getViewHolder();

	return ftlua::push(l, h->getSize());
}

int			AView::setRequestedSizeG(lua_State *l)
{
	IViewHolder *const	h = ftlua::retrieveSelf<AView>(l, -3)->getViewHolder();
	ft::Vec2<int>		s;

	s.x = luaL_checkinteger(l, -2);
	s.y = luaL_checkinteger(l, -1);
	lua_pop(l, 2);
	if (h != nullptr)
		h->setRequestedSize(s);
	return (0);
}

};
