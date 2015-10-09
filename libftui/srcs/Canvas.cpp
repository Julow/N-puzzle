// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Canvas.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:22 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/09 17:53:32 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/Canvas.hpp"
#include <cstring>

namespace ftui
{

Canvas::Canvas(ft::Color::t *bitmap, int width, int height) :
	_bitmap(bitmap),
	_width(width),
	_height(height),
	_clip(0, 0, width, height),
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

/*
** TODO: alpha
*/
ft::Color::t const	*Canvas::getBitmap(void) const
{
	return (_bitmap);
}

int				Canvas::getBitmapWidth(void) const
{
	return (_width);
}

int				Canvas::getBitmapHeight(void) const
{
	return (_height);
}

void			Canvas::clear(void)
{
	memset(_bitmap, 0, _width * _height * sizeof(ft::Color::t));
}

void			Canvas::clear(ft::Rect<int> const &rect)
{
	int const	width = rect.getWidth() * sizeof(ft::Color::t);
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

ft::Rect<int> const	&Canvas::getClip(void) const
{
	return (_clip);
}

int				Canvas::getWidth(void) const
{
	return (_clip.getWidth());
}

int				Canvas::getHeight(void) const
{
	return (_clip.getHeight());
}

void			Canvas::applyClip(ft::Rect<int> const &rect)
{
	_clip.top += rect.top;
	_clip.left += rect.left;
	_clip.setSize(ft::Vec2<int>(rect.getWidth(), rect.getHeight()));
}

void			Canvas::setClip(ft::Rect<int> const &rect)
{
	_clip = rect;
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
	int const		left = rect.left + _clip.left;
	int const		right = rect.right + _clip.left;
	ft::Color::t const	strokeColor = ft::Color::alpha(opt.strokeColor, _alpha);
	int				top;
	int				y;

	if (rect.getWidth() == 0 || rect.getHeight() == 0)
		return ;
	y = rect.bottom + _clip.top - 1;
	top = std::max(rect.bottom - opt.lineWidth, rect.top) + _clip.top;
	while (y >= top)
		putPixel(left, y--, strokeColor, rect.getWidth());
	top = rect.top + _clip.top + opt.lineWidth;
	while (y >= top)
	{
		putPixel(left, y, strokeColor, opt.lineWidth);
		putPixel(right - opt.lineWidth, y, strokeColor, opt.lineWidth);
		y--;
	}
	top -= opt.lineWidth;
	while (y >= top)
		putPixel(left, y--, strokeColor, rect.getWidth());
}

void			Canvas::fillRect(ft::Rect<int> const &rect, Params const &opt)
{
	int const	left = rect.left + _clip.left;
	int const	top = rect.top + _clip.top;
	int const	width = rect.getWidth();
	ft::Color::t const	fillColor = ft::Color::alpha(opt.fillColor, _alpha);
	int			y;

	y = rect.bottom + _clip.top;
	while (--y >= top)
		putPixel(left, y, fillColor, width);
}

Canvas			&Canvas::operator=(Canvas const &rhs)
{
	_bitmap = rhs._bitmap;
	_width = rhs._width;
	_height = rhs._height;
	_alpha = rhs._alpha;
	return (*this);
}

};
