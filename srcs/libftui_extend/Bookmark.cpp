// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bookmark.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/15 09:15:02 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/15 19:27:21 by ngoguey          ###   ########.fr       //
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
	, _text("Hello world")
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
	_holder->setRequestedSize({100, 32});
	return ;
}
void			BM::onDraw(ftui::Canvas &can)
{
	ft::Vec2<int> const		size = this->_holder->getSize();
	ft::Vec2<int> const		tsize = can.measureText(_text, {0x0, 4283782485, 12, 0});

	can.drawRect({{0, 0}, size}, {0xFFAAAAAA, 0xFF3d3838, 2, 0});
	// can.drawRect({{4, 0}, tsize}, {0, 0xFF3d3838, 0, 0});
	// can.drawRect({this->_holder->getPos(), tsize}, {0, 0xFF3d3838, 0, 0});
	can.drawText({4, size.y / 2.f - tsize.y / 2}, _text, {0x0, 0xFFAAAAAA, 12, 0});
	// can.drawText({30, 0}, _text, {0x0, 4283782485, 12, 0});
	// can.drawText({-30, 0}, _text, {0x0, 4283782485, 12, 0});
	// can.drawText({0, 30}, _text, {0x0, 4283782485, 12, 0});
	// can.drawText({0, 100}, std::to_string(size.x), {0x0, 4283782485, 12, 0});
	// can.drawText({0, 110}, std::to_string(size.y), {0x0, 4283782485, 12, 0});
	// can.drawText({0, 120}, std::to_string(this->_holder->getPos().x), {0x0, 4283782485, 12, 0});
	// can.drawText({0, 130}, std::to_string(this->_holder->getPos().y), {0x0, 4283782485, 12, 0});
	// can.drawText({0, 150}, std::to_string(tsize.x), {0x0, 4283782485, 12, 0});
	// can.drawText({0, 160}, std::to_string(tsize.y), {0x0, 4283782485, 12, 0});
	AView::onDraw(can);
	return ;
}
