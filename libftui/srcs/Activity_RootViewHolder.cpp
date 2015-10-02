/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity_RootViewHolder.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/25 09:38:59 by ngoguey           #+#    #+#             */
//   Updated: 2015/10/02 10:56:20 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/XmlParser.hpp"

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

ALayout			*Activity::RootViewHolder::getParent(void)
{ return (nullptr); }

ALayout const	*Activity::RootViewHolder::getParent(void) const
{ return (nullptr); }

AView			*Activity::RootViewHolder::getView(void)
{ return (this->_view); }

AView const		*Activity::RootViewHolder::getView(void) const
{ return (this->_view); }

Vec2<int>		Activity::RootViewHolder::getPos(void) const
{ return (Vec2<int>(0, 0)); }

Vec2<int>		Activity::RootViewHolder::getSize(void) const
{ return (this->_size); }

void			Activity::RootViewHolder::setRequestedSize(Vec2<int> size)
{
	_requestedSize = size;
}

Vec2<int>		Activity::RootViewHolder::getRequestedSize(void) const
{
	return (_requestedSize);
}

void			Activity::RootViewHolder::setParam(std::string const &k
												   , std::string const &v)
{
	(void)k;
	(void)v;
	// TODO Activity::RootViewHolder::setParam
	return ;
}


};
