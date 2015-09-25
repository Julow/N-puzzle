/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_xml.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 16:53:39 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/25 18:19:51 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "XmlParser.hpp"
#include "ft/utils.hpp"
#include <iostream>

int				main(void)
{
	ftui::XmlParser			xml(std::cin);
	ftui::XmlParser::State	state;

	if (!xml.next(state))
		return (1);
	if (state == ftui::XmlParser::State::START)
	{
		ft::f(std::cout, "START\n");
	}
	else
	{
		ft::f(std::cout, "END\n");
	}
	// while (xml.next(state))
	// {
	// 	if (state == ftui::XmlParser::State::START)
	// 	{
	// 		std::cout << "MARKUP_START <" << xml.getMarkupName() << ">" << std::endl;
	// 		for (auto p : xml.getParams())
	// 			std::cout << "\tPARAMS " << p.first << "=\"" << p.second << "\"" << std::endl;
	// 	}
	// 	else if (state == ftui::XmlParser::State::END)
	// 	{
	// 		std::cout << "MARKUP_START <" << xml.getMarkupName() << ">" << std::endl;
	// 	}
	// 	else
	// 	{
	// 		std::cout << "LOL" << std::endl;
	// 		return (1);
	// 	}
	// }
	// std::cout << "END" << std::endl;
	return (0);
}
