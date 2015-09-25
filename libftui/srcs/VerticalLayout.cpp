/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VerticalLayout.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:47 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/25 08:32:30 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "VerticalLayout.hpp"
#include "XmlParser.hpp"

namespace ftui
{

VerticalLayout::VerticalLayout(XmlParser const &xml)
	: ALayout(xml)
{
	XmlParser::params_map_t const	&params = xml.getParams();

	(void)params;
}

VerticalLayout::~VerticalLayout(void)
{
}

// VerticalLayout::VerticalLayout(VerticalLayout const &src)
// {
// 	*this = src;
// }

// VerticalLayout			&VerticalLayout::operator=(VerticalLayout const &rhs)
// {
// 	// *this = rhs;
// 	return (*this);
// }

};
