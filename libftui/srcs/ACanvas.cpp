// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ACanvas.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:22 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/05 15:06:22 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/ACanvas.hpp"
#include <cstring>

namespace ftui
{

ACanvas::ACanvas(color_t *bitmap, int width, int height) :
	_bitmap(bitmap),
	_width(width),
	_height(height),
	_alpha(1.f)
{
}

ACanvas::~ACanvas(void)
{
}

int			ACanvas::getWidth(void) const
{
	return (_width);
}

int			ACanvas::getHeight(void) const
{
	return (_height);
}

void		ACanvas::clear(ft::Rect<int> const &rect)
{
	int const	width = rect.getWidth() * sizeof(color_t);
	int			end;
	int			offset;

	offset = rect.top * _width + rect.left;
	end = rect.getHeight() * _width + offset;
	while (offset < end)
	{
		memset(_bitmap + offset, 0, width);
		offset += _width;
	}
}

float		ACanvas::getAlpha(void) const
{
	return (_alpha);
}

void		ACanvas::applyAlpha(float alpha)
{
	_alpha *= alpha;
}

void		ACanvas::setAlpha(float alpha)
{
	_alpha = alpha;
}

void		ACanvas::strokeRect(ft::Rect<int> const &rect, Params const &opt)
{
	int			y;

	if (rect.getWidth() == 0 || rect.getHeight() == 0)
		return ;
	y = rect.bottom - 1;
	putPixel(rect.left, y, opt.strokeColor, rect.getWidth());
	while (y >= rect.top)
	{
		putPixel(rect.left, y, opt.strokeColor);
		putPixel(rect.right, y, opt.strokeColor);
		y--;
	}
	putPixel(rect.left, y, opt.strokeColor, rect.getWidth());
}

void		ACanvas::fillRect(ft::Rect<int> const &rect, Params const &opt)
{
	int			y;

	y = rect.bottom;
	while (--y >= rect.top)
		putPixel(rect.left, y, opt.strokeColor, rect.getWidth());
}

// void		strokeLine(Vec2<int> a, Vec2<int> b, Params const &opt);
// void		strokeText(Vec2<int> pos, std::string const &text, Params const &opt);

};
