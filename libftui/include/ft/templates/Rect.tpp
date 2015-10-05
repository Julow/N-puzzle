/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rect.tpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/05 14:06:16 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/05 14:11:27 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{

template<typename T>
Rect::Rect(void) :
	left(0),
	top(0),
	right(0),
	bottom(0)
{
}

template<typename T>
Rect::Rect(Rect<T> const &src) :
	left(src.left),
	top(src.top),
	right(src.right),
	bottom(src.bottom)
{
}

template<typename T>
Rect::Rect(T left, T top, T right, T bottom) :
	left(left),
	top(top),
	right(right),
	bottom(bottom)
{
}

template<typename T>
Rect::Rect(Vec2<T> pos, Vec2<T> size) :
	left(pos.x),
	top(pos.y),
	right(pos.x + size.x),
	bottom(pos.y + size.y)
{
}

template<typename T>
Rect::~Rect(void)
{
}

template<typename T>
T			Rect::getWidth(void) const
{
	return (right - left);
}

template<typename T>
T			Rect::getHeight(void) const
{
	return (bottom - top);
}

template<typename T>
void		Rect::setPos(Vec2<T> pos)
{
	right = pos.x + getWidth();
	bottom = pos.y + getHeight();
	left = pos.x;
	top = pos.y;
}

template<typename T>
void		Rect::setSize(Vec2<T> size)
{
	right = left + size.x;
	bottom = top + size.y;
}

template<typename T>
bool		Rect::collides(Rect<T> const &rect) const
{
	if (rect.left <= right && rect.right >= left
		&& rect.top <= bottom && rect.bottom >= top)
		return (true);
	return (false);
}

template<typename T>
bool		Rect::collides(Rect<T> const &rect, Rect<T> &res) const
{
	if (!collides(rect))
		return (false);
	res.left = std::max(left, rect.left);
	res.top = std::max(top, rect.top);
	res.right = std::min(right, rect.right);
	res.bottom = std::min(bottom, rect.bottom);
	return (true);
}

template<typename T>
bool		Rect::contains(Rect<T> const &rect) const
{
	if (rect.left >= left && rect.top >= top
		&& rect.right <= right && rect.bottom <= bottom)
		return (true);
	return (false);
}

template<typename T>
bool		Rect::contains(Vec2<T> pt) const
{
	if (pt.x >= left && pt.x <= right
		&& pt.y >= top && pt.y <= bottom)
		return (true);
	return (false);
}

template<typename T>
void		Rect::merge(Rect<T> const &rect)
{
	if (rect.left < left)
		left = rect.left;
	if (rect.top < top)
		top = rect.top;
	if (rect.right > right)
		right = rect.right;
	if (rect.bottom > bottom)
		bottom = rect.bottom;
}

template<typename T>
void		Rect::merge(Vec2<T> pt)
{
	if (pt.x < left)
		left = pt.x;
	else if (pt.x > right)
		right = pt.x;
	if (pt.y < top)
		top = pt.y;
	else if (pt.y > bottom)
		bottom = pt.y;
}

template<typename T>
Rect<T>		&Rect::operator=(Rect<T> const &rhs)
{
	left = rhs.left;
	top = rhs.top;
	right = rhs.right;
	bottom = rhs.bottom;
	return (*this);
}

template<typename T>
bool		Rect::operator==(Rect<T> const &rhs) const
{
	return (left == rhs.left && top == rhs.top
		&& right == rhs.right && bottom == rhs.bottom);
}

};
