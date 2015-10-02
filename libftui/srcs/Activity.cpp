/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:27 by jaguillo          #+#    #+#             */
//   Updated: 2015/10/02 08:20:24 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>

#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/XmlParser.hpp"

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

void			Activity::inflate(std::istream &stream)
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

void			Activity::unregisterEvent(std::string const &event, AView *v)
{
	auto                    it = this->_eventMap.find(event);
	auto const              ite = this->_eventMap.cend();

	while (it != ite)
	{
		if (it->second->getView() == v)
			it = this->_eventMap.erase(it);
		else
			it++;
	}
	return ;
}

void			Activity::registerFun(std::string const &name
									  , void (*f)(lua_State *))
{
	(void)name;
	(void)f;
	return ;
}

};
