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

int			AView::setRequestedSizeG(lua_State *l)
{
	(void)l;
		return 0;
}

int			AView::setAlphaG(lua_State *l)
{
	// return (ftui::helperMemfun<1, 0>(
	// 			l
	// 			, std::make_tuple()
	// 			, std::make_tuple()
	// 			));
	(void)l;
	return 0;
}

int			AView::setVisibilityG(lua_State *l){(void)l; return 0;}
int			AView::setParamG(lua_State *l){(void)l; return 0;}

int			AView::hookMouseScrollG(lua_State *l){(void)l; return 0;}
int			AView::hookMouseClickG(lua_State *l){(void)l; return 0;}
int			AView::hookMoveG(lua_State *l){(void)l; return 0;}
int			AView::hookMouseCaptureG(lua_State *l){(void)l; return 0;}
int			AView::hookKeyboardG(lua_State *l){(void)l; return 0;}
int			AView::queryUpdateG(lua_State *l){(void)l; return 0;}
int			AView::queryMeasureG(lua_State *l){(void)l; return 0;}
int			AView::queryRedrawG(lua_State *l){(void)l; return 0;}

int			AView::getRequestedSizeG(lua_State *l){(void)l; return 0;}
int			AView::getPosG(lua_State *l){(void)l; return 0;}
int			AView::getSizeG(lua_State *l){(void)l; return 0;}

int			AView::getIdG(lua_State *l){(void)l; return 0;}
int			AView::getParentG(lua_State *l){(void)l; return 0;}
int			AView::getAlphaG(lua_State *l){(void)l; return 0;}
int			AView::isVisibleG(lua_State *l){(void)l; return 0;}
int			AView::isMouseOverG(lua_State *l){(void)l; return 0;}

int			AView::isMouseScrollTargetedG(lua_State *l){(void)l; return 0;}
int			AView::isMouseClickTargetedG(lua_State *l){(void)l; return 0;}
int			AView::isMouseMoveTargetedG(lua_State *l){(void)l; return 0;}
int			AView::isMouseCaptureTargetedG(lua_State *l){(void)l; return 0;}
int			AView::isKeyboardTargetedG(lua_State *l){(void)l; return 0;}
int			AView::isUpdateQueriedG(lua_State *l){(void)l; return 0;}
int			AView::isMeasureQueriedG(lua_State *l){(void)l; return 0;}
int			AView::isRedrawQueriedG(lua_State *l){(void)l; return 0;}

};
