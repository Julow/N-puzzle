/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VerticalLayout.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/26 14:38:06 by juloo            ###   ########.fr       */
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

void			VerticalLayout::onUpdate(void)
{
	AView::onUpdate();
}

void			VerticalLayout::onMeasure(void)
{
	AView::onMeasure();
}

void			VerticalLayout::onDraw(ACanvas &canvas)
{
	AView::onDraw(canvas);
}

IViewHolder		*VerticalLayout::createHolder(XmlParser const &xml,
								ALayout *p, AView *v)
{
	ViewHolder *const	holder = new ViewHolder(p, v);

	for (auto const &p : xml.getParams())
		holder->setParam(p.first, p.second);
	return (holder);
}

IViewHolder		*VerticalLayout::createHolder(ALayout *p, AView *v)
{
	return (new ViewHolder(p, v));
}

/*
** Static
*/
AView			*VerticalLayout::createView(XmlParser const &xml)
{
	return (new VerticalLayout(xml));
}

};
