// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity_RootViewHolder.cpp                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/25 09:38:59 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/09 13:29:01 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/XmlParser.hpp"

namespace ftui
{

Activity::RootViewHolder::RootViewHolder(XmlParser const &xml, AView *v
										 , ft::Vec2<int> s)
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

ft::Vec2<int>	Activity::RootViewHolder::getPos(void) const
{ return (ft::Vec2<int>(0, 0)); }

ft::Vec2<int>	Activity::RootViewHolder::getSize(void) const
{ return (this->_size); }

void			Activity::RootViewHolder::setSize(ft::Vec2<int> size)
{
	if (size == _size)
		return ;
	_size = size;
	_view->onSizeChange();
}

void			Activity::RootViewHolder::setRequestedSize(ft::Vec2<int> size)
{
	_requestedSize = size;
}

ft::Vec2<int>	Activity::RootViewHolder::getRequestedSize(void) const
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
