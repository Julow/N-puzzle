/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_xml.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 16:53:39 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/24 19:20:52 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "XmlParser.hpp"
#include <iostream>

int				main(void)
{
	ftui::XmlParser			xml(std::cin);
	ftui::XmlParser::Token	token;

	while (xml.next(token))
	{
		if (token == ftui::XmlParser::MARKUP_START)
		{
			std::cout << "MARKUP_START <" << xml.getMarkupName() << ">" << std::endl;
			for (auto p : xml.getParams())
				std::cout << "\tPARAMS " << p.first << "=\"" << p.second << "\"" << std::endl;
		}
		else if (token == ftui::XmlParser::MARKUP_END)
		{
			std::cout << "MARKUP_START <" << xml.getMarkupName() << ">" << std::endl;
		}
		else
		{
			std::cout << "LOL" << std::endl;
			return (1);
		}
	}
	std::cout << "END" << std::endl;
	return (0);
}
