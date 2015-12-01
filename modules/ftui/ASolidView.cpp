// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ASolidView.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/08 11:45:33 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/01 18:55:58 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/ASolidView.hpp"
#include "ftui/IViewHolder.hpp"
#include "ft_xml/XmlParser.hpp"
#include "ft/utils.hpp"

#include <string>

namespace ftui
{

ASolidView::ASolidView(Activity &act, std::string const &viewName) :
	AView(act, viewName), _bgParams{0x0, 0x0, 1, 0}
{
}

ASolidView::~ASolidView(void)
{
}

void			ASolidView::onDraw(ACanvas &canvas)
{
	// FTPAD("%", this->tostring());
	canvas.drawRect(canvas.getClip(), _bgParams);
	AView::onDraw(canvas);
}

void			ASolidView::setParam(std::string const &k, std::string const &v)
{
	static std::unordered_map<std::string, void (*)(ASolidView*,
		std::string const&)>	param_map
	{
		{"backgroundColor", [](ASolidView *v, std::string const &str)
		{
			v->setBackgroundColor(std::stoul(str, NULL, 16));
		}},
		{"borderColor", [](ASolidView *v, std::string const &str)
		{
			v->setBorderColor(std::stoul(str, NULL, 16));
		}},
		{"borderWidth", [](ASolidView *v, std::string const &str)
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

ft::Color::t	ASolidView::getBackgroundColor(void) const
{
	return (_bgParams.fillColor);
}

ft::Color::t	ASolidView::getBorderColor(void) const
{
	return (_bgParams.strokeColor);
}

int				ASolidView::getBorderWidth(void) const
{
	return (_bgParams.lineWidth);
}

void			ASolidView::setBackgroundColor(ft::Color::t color)
{
	_bgParams.fillColor = color;
}

void			ASolidView::setBorderColor(ft::Color::t color)
{
	_bgParams.strokeColor = color;
}

void			ASolidView::setBorderWidth(int width)
{
	_bgParams.lineWidth = width;
}

};
