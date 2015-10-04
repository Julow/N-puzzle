// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_luaCFunctions.cpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:25 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/04 11:54:00 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/AView.hpp"

namespace ftui
{

void		AView::setRequestedSize(lua_State *l){(void)l;}

void		AView::setAlpha(lua_State *l){(void)l;}
void		AView::setVisibility(lua_State *l){(void)l;}
void		AView::setParam(lua_State *l){(void)l;}

void		AView::hookMouseScroll(lua_State *l){(void)l;}
void		AView::hookMouseClick(lua_State *l){(void)l;}
void		AView::hookMove(lua_State *l){(void)l;}
void		AView::hookMouseCapture(lua_State *l){(void)l;}
void		AView::hookKeyboard(lua_State *l){(void)l;}
void		AView::queryUpdate(lua_State *l){(void)l;}
void		AView::queryMeasure(lua_State *l){(void)l;}
void		AView::queryRedraw(lua_State *l){(void)l;}

void		AView::getRequestedSize(lua_State *l){(void)l;}
void		AView::getPos(lua_State *l){(void)l;}
void		AView::getSize(lua_State *l){(void)l;}

void		AView::getId(lua_State *l){(void)l;}
void		AView::getParent(lua_State *l){(void)l;}
void		AView::getAlpha(lua_State *l){(void)l;}
void		AView::isVisible(lua_State *l){(void)l;}
void		AView::isMouseOver(lua_State *l){(void)l;}

void		AView::isMouseScrollTargeted(lua_State *l){(void)l;}
void		AView::isMouseClickTargeted(lua_State *l){(void)l;}
void		AView::isMouseMoveTargeted(lua_State *l){(void)l;}
void		AView::isMouseCaptureTargeted(lua_State *l){(void)l;}
void		AView::isKeyboardTargeted(lua_State *l){(void)l;}
void		AView::isUpdateQueried(lua_State *l){(void)l;}
void		AView::isMeasureQueried(lua_State *l){(void)l;}
void		AView::isRedrawQueried(lua_State *l){(void)l;}

};
