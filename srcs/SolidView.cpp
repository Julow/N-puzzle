// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/08 11:45:33 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/08 13:10:03 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "SolidView.hpp"
#include "ftui/IViewHolder.hpp"
#include "ftui/XmlParser.hpp"

#include <iostream> // TODO remove
#include <cstring>

namespace ftui
{

SolidView::SolidView(XmlParser const &xml, Activity &act)
	: AView(xml, act), _color(0x0)
{
}

SolidView::~SolidView(void)
{
}

void			SolidView::onDraw(Canvas &canvas)
{
	AView::onDraw(canvas);
	canvas.fillRect(ft::Rect<int>(_holder->getPos(), _holder->getSize()),
		Canvas::Params{0x0, _color});
	std::cout << "Draw " << _color << std::endl;
}

void			SolidView::setParam(std::string const &p, std::string const &v)
{
	AView::setParam(p, v);
	if (p == "color")
		_color = std::stoul(v, NULL, 16);
}

AView			*SolidView::create_view(XmlParser const &xml, Activity &act)
{
	return (new SolidView(xml, act));
}

};
