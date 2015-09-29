/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:27 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/29 08:09:35 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "Activity.hpp"
#include "AView.hpp"
#include "XmlParser.hpp"

namespace ftui
{

Activity::Activity(Vec2<int> size) :
	_rootView(NULL),
	_eventMap(),
	_size(size)
{
	return ;
}

Activity::~Activity(void)
{
	return ;
}

void				Activity::inflate(std::istream &stream)
{
	XmlParser			xml(stream);
	AView				*v;
	XmlParser::State	state;

	if (!xml.next(state))
		FTASSERT(false, "Activity should own at least 1 view");
	FTASSERT(state == XmlParser::State::START, "Cannot fail");
	v = AView::getFactory(xml.getMarkupName())(xml);
	this->_rootView = new Activity::RootViewHolder(xml, v, this->_size);
	v->inflate(xml);
	v->setViewHolder(this->_rootView);
	if (xml.next(state))
		FTASSERT(false, "Activity should not own more than 1 view");
	return ;
}

};
