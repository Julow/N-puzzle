// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/10 17:51:01 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/16 20:23:58 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/SolidView.hpp"

namespace ftui
{

SolidView::SolidView(Activity &act, ft::XmlParser const &xml) :
	ASolidView(act, xml)
{
}

SolidView::~SolidView(void)
{
}

AView			*SolidView::createView(ftui::Activity &act
									   , ft::XmlParser const *xml /* = nullptr */
									   , std::string const *id /* = nullptr */)
{
	FTASSERT(xml != nullptr || id != nullptr);
	if (xml == nullptr)
		; // return new SolidView(act, id);
	return new SolidView(act, *xml);
}

};
