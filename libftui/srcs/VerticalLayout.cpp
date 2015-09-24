/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VerticalLayout.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/24 11:50:00 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VerticalLayout.hpp"

namespace ftui
{

VerticalLayout::VerticalLayout(XmlParser &xml)
	: ALayout(xml)
{
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
