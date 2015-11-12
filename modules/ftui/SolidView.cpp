// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/10 17:51:01 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/10 17:59:57 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/SolidView.hpp"

namespace ftui
{

SolidView::SolidView(XmlParser const &xml, Activity &act) :
	ASolidView(xml, act)
{
}

SolidView::~SolidView(void)
{
}

AView			*SolidView::createView(XmlParser const &xml, Activity &act)
{
	return (new SolidView(xml, act));
}

};
