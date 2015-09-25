/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALayout.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:09 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/25 09:10:36 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "ALayout.hpp"
#include "XmlParser.hpp"

namespace ftui
{

ALayout::ALayout(XmlParser const &xml)
	: AView(xml)
{
	XmlParser::params_map_t const	&params = xml.getParams();

	(void)params;
	// TODO, retreive some ALayout data from xml
	return ;
}

ALayout::~ALayout(void)
{
}

void				ALayout::inflate(XmlParser &xml)
{
	AView				*v;
	IViewHolder			*vh;

	// TODO xml parser v2
	while (!xml.next())
	{
		if (xml.getToken() == XmlParser::MARKUP_START)
		{
			v = AView::getFactory(xml.getMarkupName())(xml);
			vh = this->createHolder(xml, this, v);
			v->inflate(xml);
			v->setViewHolder(vh);
		}
	}
	if (xml.getToken() == XmlParser::MARKUP_END)
		return ;
	// TODO throw because noway
	return ;
}


};
