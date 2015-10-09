// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ALayout.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/09 13:11:01 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/ALayout.hpp"
#include "ftui/XmlParser.hpp"
#include "ftui/IViewHolder.hpp"

#include <algorithm>
#include <iostream> //lol

using std::string;

namespace ftui
{

ALayout::ALayout(XmlParser const &xml, Activity &act)
	: AView(xml, act)
{
	XmlParser::params_map_t const	&params = xml.getParams();

	(void)params;
	// TODO, retreive some ALayout data from xml
	return ;
}

ALayout::~ALayout(void)
{
}

void				ALayout::spreadTargetMouseScroll(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_layoutFlags & AView::MOUSE_SCROLL_TARGET)
		!= state)
	{
		if (state)
			this->_layoutFlags |= AView::MOUSE_SCROLL_TARGET;
		else
		{
			this->_layoutFlags &= ~AView::MOUSE_SCROLL_TARGET;
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseScrollTargeted())
					return ;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseScroll(state);
	}
	return ;
}

void				ALayout::spreadTargetMouseClick(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_layoutFlags & AView::MOUSE_CLICK_TARGET)
		!= state)
	{
		if (state)
			this->_layoutFlags |= AView::MOUSE_CLICK_TARGET;
		else
		{
			this->_layoutFlags &= ~AView::MOUSE_CLICK_TARGET;
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseScrollTargeted())
					return ;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseClick(state);
	}
	return ;
}

void				ALayout::spreadTargetMove(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_layoutFlags & AView::MOUSE_MOVE_TARGET)
		!= state)
	{
		if (state)
			this->_layoutFlags |= AView::MOUSE_MOVE_TARGET;
		else
		{
			this->_layoutFlags &= ~AView::MOUSE_MOVE_TARGET;
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseScrollTargeted())
					return ;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMove(state);
	}
	return ;
}

void				ALayout::spreadTargetMouseCapture(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_layoutFlags & AView::MOUSE_CAPTURE_TARGET)
		!= state)
	{
		if (state)
			this->_layoutFlags |= AView::MOUSE_CAPTURE_TARGET;
		else
		{
			this->_layoutFlags &= ~AView::MOUSE_CAPTURE_TARGET;
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseScrollTargeted())
					return ;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseCapture(state);
	}
	return ;
}

void				ALayout::spreadTargetKeyboard(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_layoutFlags & AView::KEYBOARD_TARGET)
		!= state)
	{
		if (state)
			this->_layoutFlags |= AView::KEYBOARD_TARGET;
		else
		{
			this->_layoutFlags &= ~AView::KEYBOARD_TARGET;
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseScrollTargeted())
					return ;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetKeyboard(state);
	}

	return ;
}

/*
** * AView legacy *********************************************************** **
*/

void				ALayout::inflate(XmlParser &xml, Activity &a)
{
	AView				*v;
	XmlParser::State	state;

	while (xml.next(state))
	{
		std::cout << "ALayout::inflate loop" << (void*)this << std::endl; //lol
		if (state == XmlParser::State::START)
		{
			v = AView::getFactory(xml.getMarkupName())(xml, a);
			this->addView(v);
			v->inflate(xml, a);
		}
		else if (state == XmlParser::State::END)
			return ;
		else
			break ;
	}
	FTASSERT(false, "Should not be reached");
}

bool				ALayout::onMouseScroll(int x, int y, float delta)
{
	bool		ret;
	AView		*v;

	ret = false;
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isMouseScrollTargeted() && v->isMouseOver()) // TODO?? check x, y
			ret |= v->onMouseScroll(x, y, delta);
	}
	if (AView::isMouseScrollTargeted())
		ret |= AView::onMouseScroll(x, y, delta);
	return (ret);
}

bool				ALayout::onMouseDown(int x, int y, int button)
{
	bool		ret;
	AView		*v;

	ret = false;
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isMouseClickTargeted() &&
			(v->isMouseOver() || v->isMouseCaptureTargeted())) // TODO? check xy
			ret |= v->onMouseDown(x, y, button);
	}
	if (AView::isMouseClickTargeted())
		ret |= AView::onMouseDown(x, y, button);
	return (ret);
}

bool				ALayout::onMouseUp(int x, int y, int button)
{
	bool		ret;
	AView		*v;

	ret = false;
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isMouseClickTargeted() &&
			(v->isMouseOver() || v->isMouseCaptureTargeted())) // TODO? check xy
			ret |= v->onMouseUp(x, y, button);
	}
	if (AView::isMouseClickTargeted())
		ret |= AView::onMouseUp(x, y, button);
	return (ret);
}

bool				ALayout::onMouseMove(int x, int y)
{
	bool		ret;
	AView		*v;

	ret = false;
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		// TODO for childrens: call setmouseover  (before of after onmove)
		if (v->isMouseMoveTargeted() &&
			(v->isMouseOver() || v->isMouseCaptureTargeted())) // TODO? check xy
			ret |= v->onMouseMove(x, y);
	}
	if (AView::isMouseMoveTargeted())
		ret |= AView::onMouseMove(x, y);
	return (ret);
}

bool				ALayout::onKeyDown(int key_code)
{
	bool		ret;
	AView		*v;

	ret = false;
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isKeyboardTargeted())
			ret |= v->onKeyDown(key_code);
	}
	if (AView::isKeyboardTargeted())
		ret |= AView::onKeyDown(key_code);
	return (ret);
}

bool				ALayout::onKeyUp(int key_code)
{
	bool		ret;
	AView		*v;

	ret = false;
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isKeyboardTargeted())
			ret |= v->onKeyUp(key_code);
	}
	if (AView::isKeyboardTargeted())
		ret |= AView::onKeyUp(key_code);
	return (ret);
}

bool				ALayout::isMouseScrollTargeted(void) const
{
	return ((this->_layoutFlags & AView::MOUSE_SCROLL_TARGET)
			|| AView::isMouseScrollTargeted());
}

bool				ALayout::isMouseClickTargeted(void) const
{
	return ((this->_layoutFlags & AView::MOUSE_CLICK_TARGET)
			|| AView::isMouseClickTargeted());
}

bool				ALayout::isMouseMoveTargeted(void) const
{
	return ((this->_layoutFlags & AView::MOUSE_MOVE_TARGET)
			|| AView::isMouseMoveTargeted());
}

bool				ALayout::isMouseCaptureTargeted(void) const
{
	return ((this->_layoutFlags & AView::MOUSE_CAPTURE_TARGET)
			|| AView::isMouseCaptureTargeted());
}

bool				ALayout::isKeyboardTargeted(void) const
{
	return ((this->_layoutFlags & AView::KEYBOARD_TARGET)
			|| AView::isKeyboardTargeted());
}

};
