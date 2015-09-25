/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AView.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:20 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/25 09:10:46 by ngoguey          ###   ########.fr       //
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

float				AView::getAlpha(void) const
{ return (this->_alpha); }
bool				AView::isVisible(void) const
{ return (this->_flags & AView::HIDDEN); }
bool				AView::isMouseOver(void) const
{ return (this->_flags & AView::MOUSE_OVER); }

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
