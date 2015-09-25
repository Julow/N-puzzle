/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AView.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:20 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/25 11:09:43 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
#include "AView.hpp"
#include "IViewHolder.hpp"
#include "XmlParser.hpp"

namespace ftui
{

AView::AView(XmlParser const &xml)
	: _holder(NULL), _id(NULL), _flags(0), _alpha(0.f)
{
	XmlParser::params_map_t const	&params = xml.getParams();

	(void)params;
	// TODO, retreive some AView data from xml
	return ;
}

AView::~AView(void)
{
}

/*
** View core
*/
std::string const	*AView::getId(void) const
{ return (this->_id); }
ALayout				*AView::getParent(void)
{ return (this->_holder == NULL ? NULL : this->_holder->getParent()); }

void				AView::inflate(XmlParser &xml)
{
	// TODO xml parser v2
	if (!xml.next())
	{
		// TODO throw because noway
	}
	if (xml.getToken() == XmlParser::MARKUP_END)
		return ;
	// TODO throw because noway
	return ;
}

/*
** View properties
*/
float				AView::getAlpha(void) const
{ return (this->_alpha); }
bool				AView::isVisible(void) const
{ return (this->_flags & AView::HIDDEN); }
bool				AView::isMouseOver(void) const
{ return (this->_flags & AView::MOUSE_OVER); }
void				AView::setAlpha(float value)
{
	this->_alpha = value;
	//TODO finish AView::setAlpha
	(void)value;
	return ;
}
void				AView::setVisibility(bool hidden)
{
	if (hidden && !(this->_flags & AView::HIDDEN))
	{
		this->_flags &= ~AView::HIDDEN;
	}
	else if (!hidden && (this->_flags & AView::HIDDEN))
	{
		this->_flags |= AView::HIDDEN;
	}
	//TODO finish AView::setVisibility
	return ;
}

/*
** Callbacks
*/
/*
** Queries callbacks
*/
void				AView::onUpdate(void)
{
	this->_flags &= ~AView::UPDATE_QUERY;
	// TODO call lua if registered AView::onUpdate
	return ;
}
void				AView::onMeasure(void)
{
	this->_flags &= ~AView::MEASURE_QUERY;
	// TODO call lua if registered AView::onMeasure
	return ;
}
void				AView::onDraw(ACanvas &canvas)
{
	this->_flags &= ~AView::REDRAW_QUERY;
	// TODO call lua if registered AView::onDraw
	(void)canvas;
	return ;
}

/*
** Low level callbacks
*/
bool				AView::onMouseScroll(int x, int y, float delta)
{
	// TODO call lua
	(void)x;
	(void)y;
	(void)delta;
	return (false);
}
bool				AView::onMouseDown(int x, int y, int button)
{
	// TODO call lua
	(void)x;
	(void)y;
	(void)button;
	return (false);
}
bool				AView::onMouseUp(int x, int y, int button)
{
	// TODO call lua
	(void)x;
	(void)y;
	(void)button;
	return (false);
}
bool				AView::onMouseMove(int x, int y)
{
	// TODO call lua
	(void)x;
	(void)y;
	return (false);
}
bool				AView::onKeyDown(int key_code)
{
	// TODO call lua
	(void)key_code;
	return (false);
}
bool				AView::onKeyUp(int key_code)
{
	// TODO call lua
	(void)key_code;
	return (false);
}

/*
** High level callbacks
*/
void				AView::onMouseEnter(void)
{
	// TODO call lua
	return ;
}
void				AView::onMouseLeave(void)
{
	// TODO call lua
	return ;
}
void				AView::onEvent(std::string const &event)
{
	// TODO call lua
	(void)event;
	return ;
}
void				AView::onPositionChange(void)
{
	// TODO call lua
	return ;
}
void				AView::onSizeChange(void)
{
	// TODO call lua
	return ;
}
void				AView::onVisibilityChange(bool hidden)
{
	// TODO call lua
	(void)hidden;
	return ;
}


/*
** Layout system
*/
/*
** Targets
*/
bool				AView::isMouseScollTargeted(void) const
{ return (this->_flags & AView::MOUSE_SCROLL_TARGET); }
bool				AView::isMouseClickTargeted(void) const
{ return (this->_flags & AView::MOUSE_CLICK_TARGET); }
bool				AView::isMousePositionTargeted(void) const
{ return (this->_flags & AView::MOUSE_POSITION_TARGET); }
bool				AView::isKeyboardTargeted(void) const
{ return (this->_flags & AView::KEYBOARD_TARGET); }

/*
** Queries
*/
bool				AView::isRedrawQueried(void) const
{ return (this->_flags & AView::REDRAW_QUERY); }
bool				AView::isMeasureQueried(void) const
{ return (this->_flags & AView::MEASURE_QUERY); }
bool				AView::isUpdateQueried(void) const
{ return (this->_flags & AView::UPDATE_QUERY); }


/*
** View core
*/
void				AView::setMouseOver(bool over)
{
	if (over && !(this->_flags & AView::MOUSE_OVER))
	{
		this->_flags &= ~AView::MOUSE_OVER;
	}
	else if (!over && (this->_flags & AView::MOUSE_OVER))
	{
		this->_flags |= AView::MOUSE_OVER;
	}
	// TODO more AView::setMouseOver
	return ;
}

template <typename T>
typename T::ViewHolder	*AView::getHolder(void) const
{ return (dynamic_cast<typename T::ViewHolder const*>(this->_holder)); }
template <typename T>
typename T::ViewHolder	*AView::getHolder(void)
{ return (dynamic_cast<typename T::ViewHolder*>(this->_holder)); }

/*
** Static
*/
AView::factory_map_t	AView::_factories;
AView::factory_t		AView::getFactory(std::string const &name)
{
	AView::factory_t	f;

	try
	{
		f = AView::_factories.at(name);
	}
	catch (std::out_of_range &e)
	{
		std::cerr << "Factory not found" << std::endl;
		// TODO throw
	}
	return (f);
}
void					AView::registerFactory(std::string const &name,
	factory_t factory)
{
	if (!AView::_factories.insert(std::make_pair(name, factory)).second)
	{
		std::cerr << "Factory, already exists" << std::endl;
		// TODO ??
	}
	return ;
}

};
