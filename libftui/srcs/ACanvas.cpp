/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACanvas.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:14:22 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/02 18:42:50 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		ACanvas::clear(Vec2<int> pos, Vec2<int> size)
{
	int const	width = size.x * sizeof(color_t);
	int			end;
	int			offset;

	offset = pos.y * _width + pos.x;
	end = size.y * _width + offset;
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

void		ACanvas::strokeRect(Vec2<int> pos, Vec2<int> size, Params const &opt)
{
	if (size.x == 0 || size.y == 0)
		return ;
	putPixel(pos.x, pos.y, opt.strokeColor, size.x);
	size.y += pos.y;
	while (pos.y < size.y)
	{
		putPixel(pos.x, pos.y, opt.strokeColor);
		putPixel(pos.x + size.x, pos.y, opt.strokeColor);
		pos.y++;
	}
	putPixel(pos.x, pos.y, opt.strokeColor, size.x);
}

void		ACanvas::fillRect(Vec2<int> pos, Vec2<int> size, Params const &opt)
{
	size.y += pos.y;
	while (pos.y < size.y)
	{
		putPixel(pos.x, pos.y, opt.strokeColor, size.x);
		pos.y++;
	}
}

// void		strokeLine(Vec2<int> a, Vec2<int> b, Params const &opt);
// void		strokeText(Vec2<int> pos, std::string const &text, Params const &opt);

};
