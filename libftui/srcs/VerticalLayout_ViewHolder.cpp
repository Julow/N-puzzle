// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VerticalLayout_ViewHolder.cpp                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/25 10:11:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/25 10:20:08 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "VerticalLayout.hpp"
#include "XmlParser.hpp"

#include "Activity.hpp"

namespace ftui
{

VerticalLayout::ViewHolder::ViewHolder(XmlParser const &xml,
										   ALayout *p, AView *v)
	: _view(v), _parent(p)
{
	XmlParser::params_map_t const	&params = xml.getParams();

	(void)params;
}

VerticalLayout::ViewHolder::~ViewHolder(void)
{
	return ;
}

AView			*VerticalLayout::ViewHolder::getView(void)
{ return (this->_view); }
AView const		*VerticalLayout::ViewHolder::getView(void) const
{ return (this->_view); }

ALayout			*VerticalLayout::ViewHolder::getParent(void)
{ return (this->_parent); }
ALayout const	*VerticalLayout::ViewHolder::getParent(void) const
{ return (this->_parent); }

};
