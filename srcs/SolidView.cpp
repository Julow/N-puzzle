// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/08 11:45:33 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/09 15:38:47 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "SolidView.hpp"
#include "ftui/IViewHolder.hpp"
#include "ftui/XmlParser.hpp"

#include <cstring>

namespace ftui
{

SolidView::SolidView(XmlParser const &xml, Activity &act) :
	AView(xml, act), _params{0x0, 0x0, 1}
{
}

SolidView::~SolidView(void)
{
}

void			SolidView::onDraw(Canvas &canvas)
{
	AView::onDraw(canvas);
	if (_params.fillColor != 0x0)
		canvas.fillRect(ft::Rect<int>(ft::Vec2<int>(0, 0), _holder->getSize()),
			_params);
	if (_params.strokeColor != 0x0)
		canvas.strokeRect(ft::Rect<int>(ft::Vec2<int>(0, 0), _holder->getSize()),
			_params);
}

void			SolidView::setParam(std::string const &k, std::string const &v)
{
	AView::setParam(k, v);
	if (k == "fillColor") // TODO: param_map
		_params.fillColor = std::stoul(v, NULL, 16);
	else if (k == "strokeColor")
		_params.strokeColor = std::stoul(v, NULL, 16);
	else if (k == "lineWidth")
		_params.lineWidth = std::stoi(v, NULL, 16);
	else
		AView::setParam(k, v);
}

AView			*SolidView::create_view(XmlParser const &xml, Activity &act)
{
	return (new SolidView(xml, act));
}

};
