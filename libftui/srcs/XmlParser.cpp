/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:45 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/24 11:51:47 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "XmlParser.hpp"

namespace ftui
{

XmlParser::XmlParser(std::istream &stream)
	: _stream(stream)
{
}

XmlParser::~XmlParser(void)
{
}

// XmlParser::XmlParser(XmlParser const &src)
// {
// 	*this = src;
// }

// XmlParser			&XmlParser::operator=(XmlParser const &rhs)
// {
// 	// *this = rhs;
// 	return (*this);
// }

};
