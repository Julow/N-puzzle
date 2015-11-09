// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Button.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/09 14:32:22 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/09 16:15:00 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

//#include <iostream>
#include "ftui/Button.hpp"
#include "ftui/Activity.hpp"
#include "ftui/IViewHolder.hpp"

namespace ftui
{

AView		*Button::createView(XmlParser const &xml, Activity &a)
{
	return new Button(xml, a);
}

Button::Button(XmlParser const &xml, Activity &a)
	: AView(xml, a)
	, _normal{		0xFF00AA00, 0xFFFF0000, 5, 0}
	, _disabled{	0, 0, 0, 0}
	, _pushed{		0xFF00AA00, 0xFFAA0000, 2, 0}
	, _highlight{	0xFF00AA00, 0x40FFFF00, 0, 0}
{
	this->hookMouseMove(true);
	this->hookMouseClick(true);
	return ;
}

Button::~Button()
{
	return ;
}

void		Button::onDraw(Canvas &canvas)
{
	IViewHolder		*vh = this->getViewHolder();

	canvas.clearClip();
	if (this->isMouseCaptureTargeted())
		canvas.drawRect(ft::make_rect(ft::make_vec(0, 0), _holder->getSize()),
						_pushed);
	else
		canvas.drawRect(ft::make_rect(ft::make_vec(0, 0), _holder->getSize()),
						_normal);
	if (this->isMouseOver())
		canvas.drawRect({
				{5.f, 5.f}, ft::Vec2<float>(vh->getSize().x - 10, vh->getSize().y - 10)}
			, _highlight); //TODO: pas beau
	AView::onDraw(canvas);
	return ;
}

bool        Button::onMouseDown(int x, int y, int button, int mods)
{
	this->hookMouseCapture(true);
	this->queryRedraw();
	return AView::onMouseDown(x, y, button, mods) || true;
}
bool        Button::onMouseUp(int x, int y, int button, int mods)
{
	if (this->isMouseCaptureTargeted())
	{
		if (this->isMouseOver())
			this->onClick(button, mods);
		this->queryRedraw();
		this->hookMouseCapture(false);
		return AView::onMouseUp(x, y, button, mods) || true;
	}
	return AView::onMouseUp(x, y, button, mods);
}

void        Button::onMouseEnter(void)
{
	this->queryRedraw();
	AView::onMouseEnter();
	return ;
}
void        Button::onMouseLeave(void)
{
	this->queryRedraw();
	AView::onMouseLeave();
	return ;
}

void        Button::onClick(int button, int mods)
{
	this->callLuaCallback(_act.getLuaState()
						  , static_cast<uint32_t>(LuaCallback::CLICK)
						  , button, mods);
	return ;
}

};
