// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Canvas.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:22 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/08 10:51:50 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/Canvas.hpp"
#include <cstring>

namespace ftui
{

Canvas::Canvas(color_t *bitmap, int width, int height) :
	_bitmap(bitmap),
	_width(width),
	_height(height),
	_alpha(1.f)
{
}

Canvas::Canvas(Canvas const &src) :
	_bitmap(src._bitmap),
	_width(src._width),
	_height(src._height),
	_alpha(src._alpha)
{
}

Canvas::~Canvas(void)
{
}

Canvas::color_t const	*Canvas::getBitmap(void) const
{
	return (_bitmap);
}

int				Canvas::getWidth(void) const
{
	return (_width);
}

int				Canvas::getHeight(void) const
{
	return (_height);
}

void			Canvas::clear(ft::Rect<int> const &rect)
{
	int const	width = rect.getWidth() * sizeof(color_t);
	int			end;
	int			offset;

	offset = rect.top * _width + rect.left;
	end = rect.getHeight() * _width + offset;
	while (offset < end)
	{
		memset(_bitmap + offset, 0, width);
		// memset(_bitmap + offset, 0, width);
		offset += _width;
	}
}

float			Canvas::getAlpha(void) const
{
	return (_alpha);
}

void			Canvas::applyAlpha(float alpha)
{
	_alpha *= alpha;
}

void			Canvas::setAlpha(float alpha)
{
	_alpha = alpha;
}

void			Canvas::strokeRect(ft::Rect<int> const &rect, Params const &opt)
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

void			Canvas::fillRect(ft::Rect<int> const &rect, Params const &opt)
{
	int			y;

	y = rect.bottom;
	while (--y >= rect.top)
		putPixel(rect.left, y, opt.strokeColor, rect.getWidth());
}

Canvas			&Canvas::operator=(Canvas const &rhs)
{
	_bitmap = rhs._bitmap;
	_width = rhs._width;
	_height = rhs._height;
	_alpha = rhs._alpha;
	return (*this);
}

// void		strokeLine(Vec2<int> a, Vec2<int> b, Params const &opt);
// void		strokeText(Vec2<int> pos, std::string const &text, Params const &opt);

};
