// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_luaCFunctions.cpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:25 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/10 10:21:01 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/AView.hpp"
#include "ftui/luaCFunctions_helpers.hpp"

namespace ftui
{

#define DEF_LUACFUN_GSUFFIX(NAME, NUMIN, NUMOUT)			\
int			AView::NAME##G(lua_State *l)					\
{															\
	return luaCFunHelper<NUMIN, NUMOUT>(l, &AView::NAME);	\
}

// DEF_LUACFUN_GSUFFIX(setRequestedSize, 3, 0) //NYI
DEF_LUACFUN_GSUFFIX(setAlpha, 2, 0)
DEF_LUACFUN_GSUFFIX(setVisibility, 2, 0)
DEF_LUACFUN_GSUFFIX(setParam, 3, 0)
DEF_LUACFUN_GSUFFIX(hookMouseScroll, 2, 0)
DEF_LUACFUN_GSUFFIX(hookMouseClick, 2, 0)
DEF_LUACFUN_GSUFFIX(hookMouseMove, 2, 0)
DEF_LUACFUN_GSUFFIX(hookMouseCapture, 2, 0)
DEF_LUACFUN_GSUFFIX(hookKeyboard, 2, 0)
DEF_LUACFUN_GSUFFIX(queryUpdate, 1, 0)
DEF_LUACFUN_GSUFFIX(queryMeasure, 1, 0)
DEF_LUACFUN_GSUFFIX(queryRedraw, 1, 0)

// DEF_LUACFUN_GSUFFIX(getRequestedSize, 1, 2) //NYI
// DEF_LUACFUN_GSUFFIX(getPos, 1, 2) //NYI
// DEF_LUACFUN_GSUFFIX(getSize, 1, 2) //NYI
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

DEF_LUACFUN_GSUFFIX(getParent, 1, 1) //TODO untested
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

DEF_LUACFUN_GSUFFIX(getAlpha, 1, 1)
DEF_LUACFUN_GSUFFIX(isVisible, 1, 1)
DEF_LUACFUN_GSUFFIX(isMouseOver, 1, 1)
DEF_LUACFUN_GSUFFIX(isMouseScrollTargeted, 1, 1)
DEF_LUACFUN_GSUFFIX(isMouseClickTargeted, 1, 1)
DEF_LUACFUN_GSUFFIX(isMouseCaptureTargeted, 1, 1)
DEF_LUACFUN_GSUFFIX(isKeyboardTargeted, 1, 1)
DEF_LUACFUN_GSUFFIX(isUpdateQueried, 1, 1)
DEF_LUACFUN_GSUFFIX(isMeasureQueried, 1, 1)
DEF_LUACFUN_GSUFFIX(isRedrawQueried, 1, 1)

};
