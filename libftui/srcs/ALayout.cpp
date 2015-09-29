/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALayout.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:09 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/29 08:23:48 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "ALayout.hpp"
#include "XmlParser.hpp"
#include "IViewHolder.hpp"

#include <algorithm>

namespace ftui
{

ALayout::ALayout(XmlParser const &xml)
	: AView(xml)
{
	XmlParser::params_map_t const	&params = xml.getParams();

	(void)params;
	// TODO, retreive some ALayout data from xml
	return ;
}

ALayout::~ALayout(void)
{
}

void				ALayout::addView(AView *v)
{
	FTASSERT(v->getViewHolder() == nullptr);
	v->setViewHolder(this->createHolder(this, v));
	this->push_back(v->getViewHolder());
	return ;
}

AView				*ALayout::popView(AView *v)
{
	IViewHolder					*vh;
	child_container_t::iterator	it;

	vh = v->getViewHolder();
	FTASSERT(vh != nullptr
			 && vh->getParent() == this
			 &&  vh->getView() == v);
	it = std::find(this->begin(), this->end(), vh);
	FTASSERT(it != this->end());
	this->erase(it);
	delete vh;
	return (v);
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
			for (auto const &it : *this)
				if (it->getView()->isMouseScollTargeted())
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
			for (auto const &it : *this)
				if (it->getView()->isMouseScollTargeted())
					return ;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseClick(state);
	}

	return ;
}
void				ALayout::spreadTargetMousePosition(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_layoutFlags & AView::MOUSE_POSITION_TARGET)
		!= state)
	{
		if (state)
			this->_layoutFlags |= AView::MOUSE_POSITION_TARGET;
		else
		{
			this->_layoutFlags &= ~AView::MOUSE_POSITION_TARGET;
			for (auto const &it : *this)
				if (it->getView()->isMouseScollTargeted())
					return ;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMousePosition(state);
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
			for (auto const &it : *this)
				if (it->getView()->isMouseScollTargeted())
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

void				ALayout::inflate(XmlParser &xml)
{
	AView				*v;
	IViewHolder			*vh;
	XmlParser::State	state;

	while (xml.next(state))
	{
		if (state == XmlParser::State::START)
		{
			v = AView::getFactory(xml.getMarkupName())(xml);
			vh = this->createHolder(xml, this, v);
			v->inflate(xml);
			v->setViewHolder(vh);
			this->addView(v);
		}
		else if (state == XmlParser::State::END)
			return ;
		else
			break ;
	}
	FTASSERT(false, "Should not be reached");
}

void				ALayout::setParam(std::string const &k, std::string const &v)
{
	if (0)
		; //no param yet in ALayout
	else
		AView::setParam(k, v);
	return ;
}
/*
bool                ALayout::onMouseScroll(int x, int y, float delta)
{
	
	if (AView::isMouseScollTargeted())
		return (AView::onMouseScroll(x, y, delta));
	return (false);
}
bool                ALayout::onMouseDown(int x, int y, int button)
{
	// for (auto const &it : *this)
	// if (it->getView()->isMouseScollTargeted())
	// TODO call lua
	(void)x;
	(void)y;
	(void)button;
	return (false);
}
bool                ALayout::onMouseUp(int x, int y, int button)
{
	// TODO call lua
	(void)x;
	(void)y;
	(void)button;
	return (false);
}
bool                ALayout::onMouseMove(int x, int y)
{
	for (auto const &it : *this)
	{
		if (it->getView()->isMouseMoveTargeted())
		{
			it->onMouseMove(x, y);
		}
	}
	(void)x;
	(void)y;
	return (false);
}
bool                ALayout::onKeyDown(int key_code)
{
	// TODO call lua
	(void)key_code;
	return (false);
}
bool                ALayout::onKeyUp(int key_code)
{
	// TODO call lua
	(void)key_code;
	return (false);
}
*/

bool				ALayout::isMouseScollTargeted(void) const
{
	return ((this->_layoutFlags & AView::MOUSE_SCROLL_TARGET)
			|| AView::isMouseScollTargeted());
}
bool				ALayout::isMouseClickTargeted(void) const
{
	return ((this->_layoutFlags & AView::MOUSE_CLICK_TARGET)
			|| AView::isMouseClickTargeted());
}
bool				ALayout::isMousePositionTargeted(void) const
{
	return ((this->_layoutFlags & AView::MOUSE_POSITION_TARGET)
			|| AView::isMousePositionTargeted());
}
bool				ALayout::isKeyboardTargeted(void) const
{
	return ((this->_layoutFlags & AView::KEYBOARD_TARGET)
			|| AView::isKeyboardTargeted());
}

};
