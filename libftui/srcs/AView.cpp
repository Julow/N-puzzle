/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AView.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:20 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/29 09:17:51 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
#include <cstdlib>

#include "AView.hpp"
#include "ALayout.hpp"
#include "IViewHolder.hpp"
#include "XmlParser.hpp"
#include "VerticalLayout.hpp"

using std::string;

namespace ftui
{

AView::AView(XmlParser const &xml)
	: _holder(nullptr), _id(nullptr), _flags(0), _alpha(0.f)
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
{ return (this->_holder == nullptr ? nullptr : this->_holder->getParent()); }

IViewHolder			*AView::getViewHolder(void)
{ return (this->_holder); }
IViewHolder const	*AView::getViewHolder(void) const
{ return (this->_holder); }

void				AView::setViewHolder(IViewHolder *holder)
{
	FTASSERT(this->_holder == nullptr);
	this->_holder = holder;
	return ;
}

void				AView::inflate(XmlParser &xml)
{
	XmlParser::State	state;

	if (!xml.next(state))
		FTASSERT(false);
	FTASSERT(state == XmlParser::State::END);
	return ;
}

/*
** View properties
*/
float				AView::getAlpha(void) const
{ return (this->_alpha); }
bool				AView::isVisible(void) const
{ return (this->_flags & AView::HIDDEN); }
void				AView::setAlpha(float value)
{
	this->_alpha = value;
	//TODO finish AView::setAlpha
	return ;
}
void				AView::setVisibility(bool hidden)
{
	if (static_cast<bool>(this->_flags & AView::HIDDEN) != hidden)
	{
		if (hidden == true)
		{
			this->_flags |= AView::HIDDEN;
		}
		else
		{
			this->_flags &= ~AView::HIDDEN;
		}
		//TODO finish AView::setVisibility
	}
	return ;
}
bool				AView::isMouseOver(void) const
{ return (this->_flags & AView::MOUSE_OVER); }
void				AView::setParam(string const &k, string const &v)
{
	if (k == "alpha")
		this->setAlpha(::atof(v.c_str())); //TODO parser float
	else if (k == "visibility")
		this->setVisibility(v == "true"); //TODO parser bool
	else if (k == "mouse_scroll_target")
		this->registerTargetMouseScroll(v == "true"); //TODO parser bool
	else if (k == "mouse_click_target")
		this->registerTargetMouseClick(v == "true"); //TODO parser bool
	else if (k == "mouse_move_target")
		this->registerTargetMove(v == "true"); //TODO parser bool
	else if (k == "keyboard_target")
		this->registerTargetKeyboard(v == "true"); //TODO parser bool
	else if (this->_holder != nullptr)
		this->_holder->setParam(k, v);
	else
		FTASSERT(false, "Unknown param (no holder atached)");
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
bool				AView::isMouseScrollTargeted(void) const
{ return (this->_flags & AView::MOUSE_SCROLL_TARGET); }
bool				AView::isMouseClickTargeted(void) const
{ return (this->_flags & AView::MOUSE_CLICK_TARGET); }
bool				AView::isMouseMoveTargeted(void) const
{ return (this->_flags & AView::MOUSE_MOVE_TARGET); }
bool				AView::isMouseCaptureTargeted(void) const
{ return (this->_flags & AView::MOUSE_CAPTURE_TARGET); }
bool				AView::isKeyboardTargeted(void) const
{ return (this->_flags & AView::KEYBOARD_TARGET); }

/*
** Queries
*/
bool				AView::isUpdateQueried(void) const
{ return (this->_flags & AView::UPDATE_QUERY); }
bool				AView::isMeasureQueried(void) const
{ return (this->_flags & AView::MEASURE_QUERY); }
bool				AView::isRedrawQueried(void) const
{ return (this->_flags & AView::REDRAW_QUERY); }

/*
** View core
*/
void				AView::setMouseOver(bool state)
{
	if (static_cast<bool>(this->_flags & AView::MOUSE_OVER) != state)
	{
		if (state == true)
		{
			this->_flags |= AView::MOUSE_OVER;
			this->onMouseEnter();
		}
		else
		{
			this->_flags &= ~AView::MOUSE_OVER;
			this->onMouseLeave();
		}
		// TODO more AView::setMouseOver
	}
	return ;
}

template <typename T>
typename T::ViewHolder	*AView::castHolder(void) const
{
	return (dynamic_cast<typename T::ViewHolder const*>(this->_holder));
}
template <typename T>
typename T::ViewHolder	*AView::castHolder(void)
{
	return (dynamic_cast<typename T::ViewHolder*>(this->_holder));
}

/*
** Register target
** Some low level callbacks are not enabled by default
*/
void			AView::registerTargetMouseScroll(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_flags & AView::MOUSE_SCROLL_TARGET) != state)
	{
		if (state == true)
		{
			this->_flags |= AView::MOUSE_SCROLL_TARGET;
		}
		else
		{
			this->_flags &= ~AView::MOUSE_SCROLL_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseScroll(state);
	}
	return ;
}

void			AView::registerTargetMouseClick(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_flags & AView::MOUSE_CLICK_TARGET) != state)
	{
		if (state == true)
		{
			this->_flags |= AView::MOUSE_CLICK_TARGET;
		}
		else
		{
			this->_flags &= ~AView::MOUSE_CLICK_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseClick(state);
	}
	return ;
}

void			AView::registerTargetMove(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_flags & AView::MOUSE_MOVE_TARGET) != state)
	{
		if (state == true)
		{
			this->_flags |= AView::MOUSE_MOVE_TARGET;
		}
		else
		{
			this->_flags &= ~AView::MOUSE_MOVE_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMove(state);
	}
	return ;
}

void			AView::registerTargetMouseCapture(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_flags & AView::MOUSE_CAPTURE_TARGET) != state)
	{
		if (state == true)
		{
			this->_flags |= AView::MOUSE_CAPTURE_TARGET;
		}
		else
		{
			this->_flags &= ~AView::MOUSE_CAPTURE_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseCapture(state);
	}
	return ;
}

void			AView::registerTargetKeyboard(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_flags & AView::KEYBOARD_TARGET) != state)
	{
		if (state == true)
		{
			this->_flags |= AView::KEYBOARD_TARGET;
		}
		else
		{
			this->_flags &= ~AView::KEYBOARD_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetKeyboard(state);
	}
	return ;
}


/*
** Query
** Queries a callback for the next frame
*/
void			AView::queryUpdate(void)
{
	ALayout		*p;

	if ((this->_flags & AView::UPDATE_QUERY) != AView::UPDATE_QUERY)
	{
		this->_flags |= AView::UPDATE_QUERY;
		p = this->getParent();
		if (p != nullptr)
			p->queryUpdate();
	}	
	return ;
}

void			AView::queryMeasure(void)
{
	ALayout		*p;

	if ((this->_flags & AView::MEASURE_QUERY) != AView::MEASURE_QUERY)
	{
		this->_flags |= AView::MEASURE_QUERY;
		p = this->getParent();
		if (p != nullptr)
			p->queryMeasure();
	}	
	return ;
}

void			AView::queryRedraw(void)
{
	ALayout		*p;

	if ((this->_flags & AView::REDRAW_QUERY) != AView::REDRAW_QUERY)
	{
		this->_flags |= AView::REDRAW_QUERY;
		p = this->getParent();
		if (p != nullptr)
			p->queryRedraw();
	}	
	return ;
}

/*
** Static
*/
AView::factory_map_t	AView::_factories{
	{"VerticalLayout", &VerticalLayout::createView}
};

AView::factory_t		AView::getFactory(std::string const &name)
{
	AView::factory_t	f;

	// try
	// {
		f = AView::_factories.at(name);
		// Let the [] throw ?
	// }
	// catch (std::out_of_range &e)
	// {
	// 	std::cerr << "Factory not found" << std::endl;
	// 	// TODO throw in static AView::getFactory
	// }
	return (f);
}

void					AView::registerFactory(std::string const &name,
	factory_t factory)
{
	if (!AView::_factories.insert(std::make_pair(name, factory)).second)
	{
		std::cerr << "Factory, already exists" << std::endl;
		// TODO throw? static AView::registerFactory
	}
	return ;
}

};
