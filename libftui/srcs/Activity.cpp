/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:27 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/25 09:56:18 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "Activity.hpp"
#include "AView.hpp"
#include "XmlParser.hpp"

namespace ftui
{

Activity::Activity(Vec2<int> size)
	: _rootView(NULL), _eventMap(), _size(size)
{
	return ;
}

Activity::~Activity(void)
{
	return ;
}

void				Activity::inflate(std::istream &stream)
{
	// TODO xml parser v2
	XmlParser			xml(stream);
	AView				*v;

	if (!xml.next())
		;//TODO: Nothing read ?
	else
	{
		v = AView::getFactory(xml.getMarkupName())(xml);
		this->_rootView = new Activity::RootViewHolder(xml, v, this->_size);
		v->inflate(xml);
		v->setViewHolder(this->_rootView);
	}
	return ;
}

};
