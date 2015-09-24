/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AView.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:20 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/24 11:59:01 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
#include "AView.hpp"

namespace ftui
{

AView::AView(XmlParser const &xml)
	: _holder(NULL), _id(NULL), _flags(0), _alpha(0.f)
{
	// if (!xml.next() || xml.getToken() != XmlParser.MARKUP_START)
	// 	throw std::domain_error("View #%s cannot have child" % _id);
	(void)xml;
}

AView::~AView(void)
{
}

};
