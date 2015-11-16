// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ALayout.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/10 18:52:33 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/ALayout.hpp"
#include "ft_xml/XmlParser.hpp"
#include "ftui/IViewHolder.hpp"
#include "ft/utils.hpp"

#include <algorithm>
#include <iostream>

using std::string;

namespace ftui
{

ALayout::ALayout(ft::XmlParser const &xml, Activity &act) :
	ASolidView(xml, act)
{
}

ALayout::~ALayout(void)
{
}

void				ALayout::queryUpdate(void)
{
	AView::queryUpdate();
	for (int i = 0; i < size(); i++)
		at(i)->queryUpdate();
}

void				ALayout::queryMeasure(void)
{
	AView::queryMeasure();
	for (int i = 0; i < size(); i++)
		at(i)->queryMeasure();
}

void				ALayout::queryRedraw(void)
{
	AView::queryRedraw();
	for (int i = 0; i < size(); i++)
		at(i)->queryRedraw();
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
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseScrollTargeted())
					return ;
			this->_layoutFlags &= ~AView::MOUSE_SCROLL_TARGET;
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
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseClickTargeted())
					return ;
			this->_layoutFlags &= ~AView::MOUSE_CLICK_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseClick(state);
	}
	return ;
}

void				ALayout::spreadTargetMouseMove(bool state)
{
	ALayout			*p;

	FTPADB("%", (_id ? *_id : "noname"));
	if (static_cast<bool>(this->_layoutFlags & AView::MOUSE_MOVE_TARGET)
		!= state)
	{
		FTPAD("ENTERING");
		if (state)
			this->_layoutFlags |= AView::MOUSE_MOVE_TARGET;
		else
		{
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseMoveTargeted())
				{
					FTPADE();
					return ;
				}
			this->_layoutFlags &= ~AView::MOUSE_MOVE_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseMove(state);
	}
	FTPADE();
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
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseCaptureTargeted())
					return ;
			this->_layoutFlags &= ~AView::MOUSE_CAPTURE_TARGET;
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
			for (int i = 0; i < size(); i++)
				if (at(i)->isKeyboardTargeted())
					return ;
			this->_layoutFlags &= ~AView::KEYBOARD_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetKeyboard(state);
	}

	return ;
}

void				ALayout::spreadQueryUpdate(void)
{
	_layoutFlags |= AView::UPDATE_QUERY;
	if (getParent() != nullptr)
		getParent()->spreadQueryUpdate();
}

void				ALayout::spreadQueryMeasure(void)
{
	_layoutFlags |= AView::MEASURE_QUERY;
	if (getParent() != nullptr)
		getParent()->spreadQueryMeasure();
}

void				ALayout::spreadQueryRedraw(void)
{
	_layoutFlags |= AView::REDRAW_QUERY;
	if (getParent() != nullptr)
		getParent()->spreadQueryRedraw();
}


/*
** * AView legacy *********************************************************** **
*/

void				ALayout::inflate(ft::XmlParser &xml, Activity &a)
{
	AView				*v;
	ft::XmlParser::State	state;

	for (auto const &p : xml.getParams())
		setParam(p.first, p.second);
	while (xml.next(state))
	{
		if (state == ft::XmlParser::State::START)
		{
			v = AView::getFactory(xml.getMarkupName())(xml, a);
			this->addView(v);
			v->inflate(xml, a);
		}
		else if (state == ft::XmlParser::State::END)
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
		if (v->isMouseScrollTargeted() && v->isMouseOver())
			ret |= v->onMouseScroll(x, y, delta);
	}
	if (AView::isMouseScrollTargeted())
		ret |= AView::onMouseScroll(x, y, delta);
	return (ret);
}

bool				ALayout::onMouseDown(int x, int y, int button, int mods)
{
	bool		ret;
	AView		*v;

	ret = false;
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isMouseClickTargeted() &&
			(v->isMouseOver() || v->isMouseCaptureTargeted()))
			ret |= v->onMouseDown(x, y, button, mods);
	}
	if (AView::isMouseClickTargeted())
		ret |= AView::onMouseDown(x, y, button, mods);
	return (ret);
}

bool				ALayout::onMouseUp(int x, int y, int button, int mods)
{
	bool		ret;
	AView		*v;

	ret = false;
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isMouseClickTargeted() &&
			(v->isMouseOver() || v->isMouseCaptureTargeted()))
			ret |= v->onMouseUp(x, y, button, mods);
	}
	if (AView::isMouseClickTargeted())
		ret |= AView::onMouseUp(x, y, button, mods);
	return (ret);
}

bool				ALayout::onMouseMove(int x, int y)
{
	bool			ret;
	IViewHolder		*vh;
	AView			*v;

	ret = false;
	for (int i = 0; i < size(); i++)
	{
		vh = this->holderAt(i);
		v = vh->getView();
		if (v->isMouseMoveTargeted())
		{
			FTASSERT(vh != nullptr);
			if (ft::Rect<int>{vh->getPos(), vh->getSize()}.contains(
					ft::Vec2<int>{x, y}))
			{
				if (!v->isMouseOver())
					v->setMouseOver(x, y, true);
			}
			else
			{
				if (v->isMouseOver())
					v->setMouseOver(x, y, false);
			}
			if (v->isMouseOver() || v->isMouseCaptureTargeted())
				ret |= v->onMouseMove(x - vh->getPos().x, y - vh->getPos().y);
		}
	}
	if (AView::isMouseMoveTargeted())
		ret |= AView::onMouseMove(x, y);
	return (ret);
}

bool				ALayout::onKeyDown(int key_code, int mods)
{
	bool		ret;
	AView		*v;

	ret = false;
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isKeyboardTargeted())
			ret |= v->onKeyDown(key_code, mods);
	}
	if (AView::isKeyboardTargeted())
		ret |= AView::onKeyDown(key_code, mods);
	return (ret);
}

bool				ALayout::onKeyUp(int key_code, int mods)
{
	bool		ret;
	AView		*v;

	ret = false;
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isKeyboardTargeted())
			ret |= v->onKeyUp(key_code, mods);
	}
	if (AView::isKeyboardTargeted())
		ret |= AView::onKeyUp(key_code, mods);
	return (ret);
}

void				ALayout::onMouseLeave(int x, int y)
{
	AView		*v;

	AView::onMouseLeave(x, y);
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isMouseOver())
		{
			v->setMouseOver(x, y, false);
			// v->onMouseLeave(x, y);
		}
	}
	return ;
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

bool				ALayout::isUpdateQueried(void) const
{
	return ((_layoutFlags & AView::UPDATE_QUERY)
			|| AView::isUpdateQueried());
}

bool				ALayout::isMeasureQueried(void) const
{
	return ((_layoutFlags & AView::MEASURE_QUERY)
			|| AView::isMeasureQueried());
}

bool				ALayout::isRedrawQueried(void) const
{
	return ((_layoutFlags & AView::REDRAW_QUERY)
			|| AView::isRedrawQueried());
}

};
