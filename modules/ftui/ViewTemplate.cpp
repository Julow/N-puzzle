// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ViewTemplate.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/01 13:57:19 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/01 17:59:42 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/Activity.hpp"

namespace ftui
{

ViewTemplate::ViewTemplate(ft::XmlParser &xml, bool root) :
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

ViewTemplate::~ViewTemplate(void)
{
	if (_viewName != nullptr)
		delete _viewName;
	for (ViewTemplate *child : _childs)
		delete child;
}

std::string const		&ViewTemplate::getName(void) const
{
	return (*_viewName);
}

ViewTemplate::params_map_t const
						&ViewTemplate::getParams(void) const
{
	return (_params);
}

ViewTemplate::child_vector_t const
						&ViewTemplate::getChilds(void) const
{
	return (_childs);
}

};
