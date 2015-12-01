// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity_ViewTemplate.cpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/01 13:57:19 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/01 14:24:51 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/Activity.hpp"

Activity::ViewTemplate::ViewTemplate(XmlParser &xml, bool root = true) :
	_viewName(root ? nullptr : new std::string(xml.getMarkupName())),
	_params(xml.getParams()),
	_childs()
{
	ft::XmlParser::State	state;

	while (xml.next(state))
	{
		if (state == ft::XmlParser::State::START)
			_childs.push_back(new ViewTemplate(xml, false));
		else if (state == ft::XmlParser::State::END)
			return ;
		else
			break ;
	}
	FTASSERT(false, "Should not be reached");
}

Activity::ViewTemplate::~ViewTemplate(void)
{
	if (_viewName != nullptr)
		delete _viewName;
	for (ViewTemplate *child : _childs)
		delete child;
}

param_map_t const	&Activity::ViewTemplate::getParams(void) const
{
	return (_params);
}
