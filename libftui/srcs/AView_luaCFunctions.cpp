// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_luaCFunctions.cpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:25 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/05 14:29:39 by ngoguey          ###   ########.fr       //
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
// DEF_LUACFUN_GSUFFIX(getId, 1, 1) //custom function
// DEF_LUACFUN_GSUFFIX(getParent, 1, 1) //custom function
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
