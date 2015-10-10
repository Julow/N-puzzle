// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/08 11:45:33 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/10 16:33:30 by jaguillo         ###   ########.fr       //
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
	static std::unordered_map<std::string, void (*)(SolidView*, std::string const&)>	param_map
	{
		{"fillColor", [](SolidView *v, std::string const &str)
		{
			v->_params.fillColor = std::stoul(str, NULL, 16);
		}},
		{"strokeColor", [](SolidView *v, std::string const &str)
		{
			v->_params.strokeColor = std::stoul(str, NULL, 16);
		}},
		{"lineWidth", [](SolidView *v, std::string const &str)
		{
			v->_params.lineWidth = std::stoi(str, NULL);
		}}
	};
	auto const	&it = param_map.find(k);
	if (it != param_map.end())
		it->second(this, v);
	else
		AView::setParam(k, v);
}

AView			*SolidView::create_view(XmlParser const &xml, Activity &act)
{
	return (new SolidView(xml, act));
}

};
