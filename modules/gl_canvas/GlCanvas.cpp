// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GlCanvas.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/24 10:07:06 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/07 17:36:43 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "gl_canvas/GlCanvas.hpp"
#include <cstring>

namespace gl
{

GlCanvas::GlCanvas(ft::Color::t *bitmap, int width, int height) :
	ACanvas(width, height),
	_bitmap(bitmap)
{
}

GlCanvas::~GlCanvas(void)
{
}

ft::Color::t const	*GlCanvas::getBitmap(void) const
{
	return (_bitmap);
}

void			GlCanvas::setBitmap(ft::Color::t *bitmap)
{
	_bitmap = bitmap;
}

void			GlCanvas::clear(void)
{
	std::memset(_bitmap, 0, _width * _height * sizeof(ft::Color::t));
	this->applyChangedRect(ft::make_rect(0, 0, _width, _height));
}

void			GlCanvas::clear(ft::Rect<int> const &rect)
{
	int const	width = rect.getWidth() * sizeof(ft::Color::t);
	int			end;
	int			offset;

	this->applyChangedRect(rect);
	offset = rect.top * _width + rect.left;
	end = rect.getHeight() * _width + offset;
	while (offset < end)
	{
		std::memset(_bitmap + offset, 0, width);
		offset += _width;
	}
}

void			GlCanvas::_putAlphaBitmap(ft::Vec2<int> pos, uint8_t const *bitmap,
					ft::Rect<int> const &rect, int pitch, ft::Color::t color)
{
	int const		max_x = std::min(rect.right, _clip.right - pos.x);
	int const		max_y = std::min(rect.bottom, _clip.bottom - pos.y);
	int				x;
	int				y;

	y = std::max(rect.top, _clip.top - pos.y);
	while (y < max_y)
	{
		x = std::max(rect.left, _clip.left - pos.x);
		while (x < max_x)
		{
			if (bitmap[x] > 0)
				putPixel(x + pos.x, y + pos.y,
					ft::Color::alpha(color, bitmap[x]));
			x++;
		}
		y++;
		bitmap += pitch;
	}
}

void			GlCanvas::_strokeRect(ft::Rect<int> const &rect,
					ft::Color::t color, int lineWidth)
{
	if (!rect)
		return ;
	_fillRect(ft::make_rect(rect.left, rect.top,
			rect.right, rect.top + lineWidth), color);
	_fillRect(ft::make_rect(rect.right - lineWidth, rect.top + lineWidth,
			rect.right, rect.bottom - lineWidth), color);
	_fillRect(ft::make_rect(rect.left, rect.bottom - lineWidth,
			rect.right, rect.bottom), color);
	_fillRect(ft::make_rect(rect.left, rect.top + lineWidth,
			rect.left + lineWidth, rect.bottom - lineWidth), color);
}

void			GlCanvas::_fillRect(ft::Rect<int> const &rect, ft::Color::t color)
{
	int const	left = std::max(rect.left, _clip.left);
	int const	top = std::max(rect.top, _clip.top);
	int const	width = std::min(rect.right, _clip.right) - left;
	int			y;

	y = std::min(rect.bottom, _clip.bottom);
	if (width > 0)
		while (--y >= top)
			putPixel(left, y, color, width);
}

};
