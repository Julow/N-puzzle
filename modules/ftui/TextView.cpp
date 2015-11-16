// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TextView.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/12 08:49:42 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/09 13:17:47 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/TextView.hpp"
#include "ftui/IViewHolder.hpp"

#include <string>

namespace ftui
{

TextView::TextView(ft::XmlParser const &xml, Activity &a) :
	ASolidView(xml, a), _text(""), _textParams{0x0, 0x0, 16, 0}
{
}

TextView::~TextView(void)
{
}

void				TextView::onMeasure(void)
{
	ASolidView::onMeasure();
	_holder->setRequestedSize(Canvas::measureText(_text, _textParams));
}

void				TextView::onDraw(Canvas &canvas)
{
	ASolidView::onDraw(canvas);
	canvas.drawText(ft::make_vec(0.f, 0.f), _text, _textParams);
}

std::string const	&TextView::getText(void) const
{
	return (_text);
}

void				TextView::setText(std::string const &text)
{
	_text = text;
}

Canvas::font_t		TextView::getFont(void) const
{
	return (_textParams.font);
}

void				TextView::setFont(Canvas::font_t font)
{
	_textParams.font = font;
}

ft::Color::t		TextView::getTextColor(void) const
{
	return (_textParams.fillColor);
}

void				TextView::setTextColor(ft::Color::t color)
{
	_textParams.fillColor = color;
}

int32_t				TextView::getTextSize(void) const
{
	return (_textParams.lineWidth);
}

void				TextView::setTextSize(int32_t size)
{
	_textParams.lineWidth = size;
}

void				TextView::setParam(std::string const &k,
						std::string const &v)
{
	static std::unordered_map<std::string, void (*)(TextView*,
		std::string const&)>	param_map
	{
		{"text", [](TextView *v, std::string const &str)
		{
			v->setText(str);
		}},
		{"textFont", [](TextView *v, std::string const &str)
		{
			v->setFont(Canvas::getFont(str));
		}},
		{"textColor", [](TextView *v, std::string const &str)
		{
			v->setTextColor(std::stoul(str, NULL, 16));
		}},
		{"textSize", [](TextView *v, std::string const &str)
		{
			v->setTextSize(std::stoi(str, NULL));
		}}
	};
	auto const		&it = param_map.find(k);

	if (it != param_map.end())
		it->second(this, v);
	else
		ASolidView::setParam(k, v);
}

AView				*TextView::createView(ft::XmlParser const &xml, Activity &a)
{
	return (new TextView(xml, a));
}

};
