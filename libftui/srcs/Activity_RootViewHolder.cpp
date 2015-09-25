// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity_RootViewHolder.cpp                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/25 09:38:59 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/25 10:14:28 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Activity.hpp"
#include "AView.hpp"
#include "XmlParser.hpp"

namespace ftui
{

Activity::RootViewHolder::RootViewHolder(XmlParser const &xml, AView *v
										 , Vec2<int> s)
	: _view(v), _size(s)
{
	XmlParser::params_map_t const   &params = xml.getParams();

	(void)params;
	return ;
}

Activity::RootViewHolder::~RootViewHolder(void)
{
	return ;
}

AView           *Activity::RootViewHolder::getView(void)
{ return (this->_view); }
AView const		*Activity::RootViewHolder::getView(void) const
{ return (this->_view); }

Vec2<int>       Activity::RootViewHolder::getPos(void) const
{ return (Vec2<int>(0, 0)); }
Vec2<int>       Activity::RootViewHolder::getSize(void) const
{ return (this->_size); }

};
