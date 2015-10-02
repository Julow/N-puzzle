/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rect.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 18:43:04 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/02 19:09:29 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECT_HPP
# define RECT_HPP

# include "Vec.hpp"

namespace ft
{

/*
** Represent a Rect
*/
template<typename T>
class	Rect
{
public:
	Rect(void) :
		x(0),
		y(0),
		width(0),
		height(0) {}
	Rect(Rect<T> const &src) :
		x(src.x),
		y(src.y),
		width(src.width),
		height(src.height) {}
	Rect(Vec2<T> pos, Vec2<T> size) :
		x(pos.x),
		y(pos.y),
		width(size.x),
		height(size.y) {}
	Rect(Vec4<T> const &vec) :
		x(vec.x),
		y(vec.y),
		width(vec.z),
		height(vec.w) {}
	Rect(T x, T y, T width, T height) :
		x(x),
		y(y),
		width(width),
		height(height) {}

	T			x;
	T			y;
	T			width;
	T			height;

/*
** Extend to overlap 'rect'
*/
	// void		merge(Rect<T> const &rect)
	// {
	// 	if (x > rect.x)
	// 	{
	// 		width += x - rect.x;
	// 		x = rect.x;
	// 	}
	// 	if (y > rect.y)
	// 	{
	// 	}
	// }

/*
** Clamp to fit inside 'bounds'
** Clamped rect are not moved outside it's old bounds
**  (except if width or height are set to 0)
*/
	void		clamp(Rect<T> const &bounds)
	{
		if (x < bounds.x)
		{
			width -= bounds.x - x;
			x = bounds.x;
		}
		if (y < bounds.y)
		{
			height -= bounds.y - y;
			y += bounds.y;
		}
		if (width > bounds.width)
			width = bounds.width;
		else if (width < 0)
			width = 0;
		if (height > bounds.height)
			height = bounds.height;
		else if (height < 0)
			height = 0;
	}

/*
** Operators
*/
	Rect<T>		&operator=(Rect<T> const &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		width = rhs.width;
		height = rhs.height;
		return (*this);
	}

	bool		operator==(Rect<T> const &rhs) const
	{
		return (x == rhs.x && y == rhs.y
			&& width == rhs.width && height == rhs.height);
	}

protected:
private:
};

};

#endif
