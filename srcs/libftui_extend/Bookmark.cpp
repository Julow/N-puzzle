// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bookmark.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/15 09:15:02 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/15 09:44:46 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "libftui_extend/Bookmark.hpp"
#include "ftui/Canvas.hpp"

using BM = Bookmark;

// ========================================================================== //
// CONSTRUCTION
//

void			BM::declare_libftui(void)
{
	AView::defineView("Bookmark", "AView", &BM::createView);
	return ;
}

ftui::AView		*BM::createView(ftui::XmlParser const &xml, ftui::Activity &act)
{
	return new Bookmark(xml, act);
}

BM::Bookmark(ftui::XmlParser const &xml, ftui::Activity &act)
	: AView(xml, act)
{
	return ;
}

BM::~Bookmark()
{ }

// ========================================================================== //
// DRAW
//

void			BM::onMeasure(void)
{
	_holder->setRequestedSize({40, 20});
	return ;
}
void			BM::onDraw(ftui::Canvas &can)
{
	ft::Vec2<int> const		size = this->_holder->getSize();

	can.drawRect({{0, 0}, size}, {0, 0xFF3d3838, 0, 0});
	// can.drawRect({this->_holder->getPos(), size}, {0, 0xFF3d3838, 0, 0});
	AView::onDraw(can);
	return ;
}
