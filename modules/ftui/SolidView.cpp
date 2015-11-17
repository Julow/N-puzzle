// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/10 17:51:01 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/17 15:02:51 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/SolidView.hpp"

namespace ftui
{

/* ************************************************************************** **
** CONSTRUCTION
*/

AView			*SolidView::createView(
	ftui::Activity &act, ft::XmlParser const *xml, std::string const *id)
{
	FTASSERT((xml == nullptr) != (id == nullptr));
	if (xml == nullptr)
		return new SolidView(act, id);
	return new SolidView(act, *xml);
}

SolidView::SolidView(Activity &act, ft::XmlParser const &xml)
	: ASolidView(act, xml)
{
}

SolidView::SolidView(Activity &act, std::string const *id
					 , std::string const &viewName /* = "SolidView" */)
	: ASolidView(act, id, viewName)
{
}

SolidView::~SolidView(void)
{
}

};
