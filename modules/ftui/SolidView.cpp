// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/10 17:51:01 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/01 18:57:15 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/SolidView.hpp"

namespace ftui
{

/* ************************************************************************** **
** CONSTRUCTION
*/

AView			*SolidView::createView(ftui::Activity &act)
{
	return (new SolidView(act));
}

SolidView::SolidView(Activity &act, std::string const &viewName /* = "SolidView" */)
	: ASolidView(act, viewName)
{
}

SolidView::~SolidView(void)
{
}

};
