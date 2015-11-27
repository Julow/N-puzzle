// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Rect.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/02 18:43:04 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/27 16:33:53 by juloo            ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef RECT_HPP
# define RECT_HPP

# include "ft/Vec.hpp"

namespace ft
{

/*
** Represent a Rect
** -
** All functions assumes top <= bottom && left <= right
*/
template<typename T>
class	Rect
{
public:
	Rect(void);
	Rect(Rect<T> const &src);
	Rect(T left, T top, T right, T bottom);
	Rect(Vec2<T> pos, Vec2<T> size);
	~Rect(void);

	T			left;
	T			top;
	T			right;
	T			bottom;

/*
** Bounds
*/

	/*
	** Move the rect and keep it's size
	*/
	void		setPos(Vec2<T> pos);
	void		setPos(T x, T y);
	Vec2<T>		getPos(void) const;
	void		setX(T x);
	void		setY(T y);

	void		setSize(Vec2<T> size);
	void		setSize(T w, T h);
	Vec2<T>		getSize(void) const;

	T			getWidth(void) const;
	void		setWidth(T w);
	T			getHeight(void) const;
	void		setHeight(T h);

	/*
	** Expand the rect in all directions
	*/
	void		expand(T exp);

/*
** Checks
*/
	/*
	** Check collision with 'rect'
	*/
	bool		collides(Rect<T> const &rect) const;

	/*
	** Check collision with 'rect'
	** Set 'res' to the surface of the collision
	** Does not update 'res' if the rects doesn't collide
	*/
	bool		collides(Rect<T> const &rect, Rect<T> &res) const;

	/*
	** Check if 'rect' fit in the rect
	*/
	bool		contains(Rect<T> const &rect) const;

	/*
	** Check if pt is into the rect's bounds
	*/
	bool		contains(Vec2<T> pt) const;

/*
** Operations
*/
	/*
	** Enlarge the rect to contains 'rect'
	*/
	void		merge(Rect<T> const &rect);

	/*
	** Enlarge the rect to contains 'pt'
	*/
	void		merge(Vec2<T> pt);

/*
** With
** -
** Return a new rectangle changing a property
*/
	Rect<T>		with(T x, T y, T w, T h) const;

/*
** Operators
*/
	Rect<T>		&operator=(Rect<T> const &rhs);

	/*
	** Check if the rect is empty
	** (width <= 0 || height <= 0)
	*/
	operator bool(void) const;

	/*
	** Offset the rect
	*/
	Rect<T>		operator+(Vec2<T> offset) const;
	Rect<T>		&operator+=(Vec2<T> offset);
	Rect<T>		operator-(Vec2<T> offset) const;
	Rect<T>		&operator-=(Vec2<T> offset);

	/*
	** Scale the rect
	*/
	Rect<T>		operator*(T scale) const;
	Rect<T>		&operator*=(T scale);

	/*
	** TODO: float comparaison
	*/
	bool		operator==(Rect<T> const &rhs) const;

	/*
	** Cast
	*/
	template<typename C>
	operator Rect<C>(void) const;

protected:
private:
};

template<typename T>
Rect<T>		make_rect(T left, T top, T right, T bottom);
template<typename T>
Rect<T>		make_rect(Vec2<T> pos, Vec2<T> size);
template<typename T>
Rect<T>		operator^(Vec2<T> pos, Vec2<T> size);

};

# include "ft/templates/Rect.tpp"

#endif
