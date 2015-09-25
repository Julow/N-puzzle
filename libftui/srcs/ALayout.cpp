/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALayout.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:09 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/25 16:04:25 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "ALayout.hpp"
#include "XmlParser.hpp"
#include "IViewHolder.hpp"

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

void				ALayout::addView(AView *v)
{
	if (v->getViewHolder() != nullptr)
		; //TODO: throw view with two parents
	v->setViewHolder(this->createHolder(this, v));
	this->push_back(v->getViewHolder());
	return ;
}

AView				*ALayout::popView(AView *v)
{
	IViewHolder					*vh;
	child_container_t::iterator	it;

	vh = v->getViewHolder();
	if (vh == nullptr
		|| vh->getParent() != this
		|| vh->getView() != v)
		; // TODO: throw, (view, viewholder) pair invalid before pop
	it = find(this->begin(), this->end(), vh);
	if (it == this->end())
		; // TODO; throw, trying to remove element not in vector
	this->erase(it);
	delete vh;
	return (v);
}



/*
** * AView legacy *********************************************************** **
*/

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
			this->addView(v);
		}
	}
	if (xml.getToken() == XmlParser::MARKUP_END)
		return ;
	// TODO throw because noway
	return ;
}

void				ALayout::setParam(std::string const &k, std::string const &v)
{
	if (0)
		; //no param yet
	else
		AView::setParam(k, v);
	return ;
}

};
