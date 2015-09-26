/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_xml.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 16:53:39 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/26 13:58:05 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "XmlParser.hpp"
#include "ft/utils.hpp"
#include <iostream>
#include <iomanip>

static void		xml_test(ftui::XmlParser &xml, int indent)
{
	ftui::XmlParser::State	state;

	while (xml.next(state))
		if (state == ftui::XmlParser::State::START)
		{
			std::cout << std::setfill('\t') << std::setw(indent + 1);
			ft::f(std::cout, "<%", xml.getMarkupName());
			for (auto p : xml.getParams())
				ft::f(std::cout, " %=\"%\"", p.first, p.second);
			std::cout << ">" << std::endl;
			xml_test(xml, indent + 1);
		}
		else if (state == ftui::XmlParser::State::END)
		{
			std::cout << std::setfill('	') << std::setw(indent);
			ft::f(std::cout, "</>\n");
			return ;
		}
	std::cout << std::setfill('\t') << std::setw(indent) << "NEXT FAIL" << std::endl;
}

int				main(void)
{
	ftui::XmlParser			xml(std::cin);

	xml_test(xml, 0);
	return (0);
}
