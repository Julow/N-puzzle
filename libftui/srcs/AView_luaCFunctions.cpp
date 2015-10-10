// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_luaCFunctions.cpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:25 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/10 18:40:04 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/AView.hpp"
#include "ftui/IViewHolder.hpp"
#include "ftui/ASolidView.hpp"
#include "ftui/luaCFunctions_helpers.hpp"

namespace ftui
{

#define DEF_LUACFUN_GSUFFIX(CLASS, NAME, NUMIN, NUMOUT)			\
int			CLASS::NAME##G(lua_State *l)						\
{																\
	return luaCFunHelper<NUMIN, NUMOUT>(l, &CLASS::NAME);		\
}

#define DEF_LUACFUN_G_CAST(CLASS, NAME, NUMIN, NUMOUT, RET, ...)		\
int			CLASS::NAME##G(lua_State *l)								\
{																		\
	return luaCFunHelper<NUMIN, NUMOUT>(l,								\
		reinterpret_cast<RET (CLASS::*)(__VA_ARGS__)>(&CLASS::NAME));	\
}

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
DEF_LUACFUN_GSUFFIX(AView, getParent,				1,	1) //TODO untested

DEF_LUACFUN_GSUFFIX(ASolidView, getBorderWidth,		1,	1) // TODO: untested
DEF_LUACFUN_GSUFFIX(ASolidView, setBorderWidth,		2,	0) // TODO: untested

DEF_LUACFUN_G_CAST(ASolidView, getBackgroundColor,	1,	1, int) // TODO: untested
DEF_LUACFUN_G_CAST(ASolidView, getBorderColor,		1,	1, int) // TODO: untested
DEF_LUACFUN_G_CAST(ASolidView, setBackgroundColor,	2,	0, void, int) // TODO: untested
DEF_LUACFUN_G_CAST(ASolidView, setBorderColor,		2,	0, void, int) // TODO: untested

int			AView::getIdG(lua_State *l)
{
	AView *const				i = luaCFunRetreiveSelf<AView>(l, -1);
	std::string const *const	s = i->getId();

	if (s == nullptr)
		lua_pushnil(l);
	else
		lua_pushstring(l, s->c_str());
	return (1);
}

// int			AView::getParentG(lua_State *l)
// {
// 	AView *const	i = luaCFunRetreiveSelf<AView>(l, -1);
// 	ALayout *const	p = i->getParent();
	
// 	if (p == nullptr)
// 		lua_pushnil(l);
// 	else
// 	{
// 		lua_pushglobaltable(l);
// 		lua_pushlightuserdata(l, p);
// 		lua_gettable(l, -2);
// 	}
// 	return (1);
// }

int			AView::getRequestedSizeG(lua_State *l)
{
	IViewHolder *const	h = luaCFunRetreiveSelf<AView>(l, -1)->getViewHolder();
	ft::Vec2<int>		s;

	if (h == nullptr)
		return (0);
	s = h->getRequestedSize();
	lua_pushinteger(l, s.x);
	lua_pushinteger(l, s.y);
	return (2);
}

int			AView::getPosG(lua_State *l)
{
	IViewHolder *const	h = luaCFunRetreiveSelf<AView>(l, -1)->getViewHolder();
	ft::Vec2<int>		s;

	if (h == nullptr)
		return (0);
	s = h->getPos();
	lua_pushinteger(l, s.x);
	lua_pushinteger(l, s.y);
	return (2);
}

int			AView::getSizeG(lua_State *l)
{
	IViewHolder *const	h = luaCFunRetreiveSelf<AView>(l, -1)->getViewHolder();
	ft::Vec2<int>		s;

	if (h == nullptr)
		return (0);
	s = h->getSize();
	lua_pushinteger(l, s.x);
	lua_pushinteger(l, s.y);
	return (2);
}

int			AView::setRequestedSizeG(lua_State *l)
{
	IViewHolder *const	h = luaCFunRetreiveSelf<AView>(l, -3)->getViewHolder();
	ft::Vec2<int>		s;

	s.x = luaL_checkinteger(l, -1);
	s.y = luaL_checkinteger(l, -2);
	lua_pop(l, 2);
	if (h == nullptr)
		h->setRequestedSize(s);
	return (0);
}

};
