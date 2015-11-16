// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Button.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/09 14:32:22 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/16 13:42:58 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

//#include <iostream>
#include "ftui/Button.hpp"
#include "ftui/Activity.hpp"
#include "ftui/IViewHolder.hpp"

namespace ftui
{

using namespace std::chrono_literals;

Button::time_point const	Button::_zero =
	std::chrono::system_clock::from_time_t(0);
Button::time_diff const	Button::_maxDelta =
	300ms;

/* ************************************************************************** **
** CONSTRUCTION
*/

AView		*Button::createView(ft::XmlParser const &xml, Activity &a)
{
	return new Button(xml, a);
}

Button::Button(ft::XmlParser const &xml, Activity &a)
	: AView(xml, a)
	, _state(true)
	, _normal{		0xFF00AA00, 0xFFFF0000, 5, 0}
	, _disabled{	0, 0, 0, 0}
	, _pushed{		0xFF00AA00, 0xFFAA0000, 2, 0}
	, _highlight{	0xFF00AA00, 0x40FFFF00, 0, 0}
	, _lastClick(_zero)
{
	return ;
}

Button::Button(Activity &act, std::string const *id
			   , std::string const &viewName /* = "Button" */)
	: AView(act, id, viewName)
	, _state(true)
	, _normal{		0xFF00AA00, 0xFFFF0000, 5, 0}
	, _disabled{	0, 0, 0, 0}
	, _pushed{		0xFF00AA00, 0xFFAA0000, 2, 0}
	, _highlight{	0xFF00AA00, 0x40FFFF00, 0, 0}
	, _lastClick(_zero)
{
	return ;
}

Button::~Button()
{
	return ;
}

void		Button::inflate(ft::XmlParser &xml, Activity &act)
{
	AView::inflate(xml, act);
	return ;
}

void		Button::setViewHolder(IViewHolder *holder)
{
	//TODO: onViewHolderChange
	if (holder == nullptr)
	{
		this->hookMouseMove(false);
		this->hookMouseClick(false);
	}
	AView::setViewHolder(holder);
	if (holder != nullptr)
	{
		this->hookMouseMove(true);
		this->hookMouseClick(true);
	}
	return ;
}

/* ************************************************************************** **
** DRAW
*/

void		Button::onDraw(Canvas &canvas)
{
	IViewHolder		*vh = this->getViewHolder();

	// canvas.clearClip();
	if (this->isMouseCaptureTargeted())
		canvas.drawRect(ft::make_rect(ft::make_vec(0, 0), _holder->getSize()),
						_pushed);
	else if (_state == true)
		canvas.drawRect(ft::make_rect(ft::make_vec(0, 0), _holder->getSize()),
						_normal);
	else
		canvas.drawRect(ft::make_rect(ft::make_vec(0, 0), _holder->getSize()),
						_disabled);
	if (this->isMouseOver())
		canvas.drawRect({
				{5.f, 5.f}
				, ft::Vec2<float>(vh->getSize().x - 10, vh->getSize().y - 10)}
			, _highlight); //TODO: pas beau
	AView::onDraw(canvas);
	return ;
}

/* ************************************************************************** **
** MOUSE EVENTS
*/

bool        Button::onMouseDown(int x, int y, int button, int mods)
{
	if (button == 0)
	{
		this->hookMouseCapture(true);
		this->queryRedraw();
	}
	return AView::onMouseDown(x, y, button, mods);
}

bool        Button::onMouseUp(int x, int y, int button, int mods)
{
	if (this->isMouseCaptureTargeted())
	{
		if (button == 0 && this->isMouseOver())
		{
			if (_lastClick != _zero
				&& std::chrono::system_clock::now() - _lastClick < _maxDelta)
			{
				// 1. Validate button double click
				_lastClick = _zero;
				this->onDoubleClick(mods);
			}
			else
			{
				// 2. Validate button click
				_lastClick = std::chrono::system_clock::now();
				this->onClick(mods);
			}
			this->queryRedraw();
			this->hookMouseCapture(false);
			return AView::onMouseUp(x, y, button, mods) || true;
		}
		// 3. Abort button click
		this->queryRedraw();
		this->hookMouseCapture(false);
	}
	// 4. Was not clicking
	return AView::onMouseUp(x, y, button, mods);
}

void        Button::onMouseEnter(int x, int y)
{
	this->queryRedraw();
	AView::onMouseEnter(x, y);
	return ;
}

void        Button::onMouseLeave(int x, int y)
{
	this->queryRedraw();
	AView::onMouseLeave(x, y);
	return ;
}


void        Button::onClick(int mods)
{
	this->callLuaCallback(
		_act.getLuaState()
		, static_cast<uint32_t>(LuaCallback::CLICK), mods, 0);
	//TODO: does not compile without the trailing '0'
	return ;
}

void        Button::onDoubleClick(int mods)
{
	this->callLuaCallback(
		_act.getLuaState()
		, static_cast<uint32_t>(LuaCallback::DOUBLE_CLICK), mods, 0);
	//TODO: does not compile without the trailing '0'
	return ;
}

/* ************************************************************************** **
** INTERACTIONS
*/

void		Button::setState(bool state)
{
	if (state != _state)
	{
		_state = state;
		this->queryRedraw();
	}
	return ;
}

bool		Button::getState(void)
{
	return _state;
}

};
