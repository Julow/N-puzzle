// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/08 11:45:33 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/10 17:33:41 by jaguillo         ###   ########.fr       //
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
	if (ft::Color::a(_params.fillColor) != 0)
		canvas.fillRect(ft::Rect<int>(ft::Vec2<int>(0, 0), _holder->getSize()),
			_params);
	if (ft::Color::a(_params.strokeColor) != 0)
		canvas.strokeRect(ft::Rect<int>(ft::Vec2<int>(0, 0),
			_holder->getSize()), _params);
}

void			SolidView::setParam(std::string const &k, std::string const &v)
{
	static std::unordered_map<std::string, void (*)(SolidView*,
		std::string const&)>	param_map
	{
		{"backgroundColor", [](SolidView *v, std::string const &str)
		{
			v->setBackgroundColor(std::stoul(str, NULL, 16));
		}},
		{"borderColor", [](SolidView *v, std::string const &str)
		{
			v->setBorderColor(std::stoul(str, NULL, 16));
		}},
		{"borderWidth", [](SolidView *v, std::string const &str)
		{
			v->setBorderWidth(std::stoi(str, NULL));
		}}
	};
	auto const		&it = param_map.find(k);

	if (it != param_map.end())
		it->second(this, v);
	else
		AView::setParam(k, v);
}

ft::Color::t	SolidView::getBackgroundColor(void) const
{
	return (_params.fillColor);
}

ft::Color::t	SolidView::getBorderColor(void) const
{
	return (_params.strokeColor);
}

int				SolidView::getBorderWidth(void) const
{
	return (_params.lineWidth);
}

void			SolidView::setBackgroundColor(ft::Color::t color)
{
	_params.fillColor = color;
}

void			SolidView::setBorderColor(ft::Color::t color)
{
	_params.strokeColor = color;
}

void			SolidView::setBorderWidth(int width)
{
	_params.lineWidth = width;
}

AView			*SolidView::create_view(XmlParser const &xml, Activity &act)
{
	return (new SolidView(xml, act));
}

};
