/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rect.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 18:43:04 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/05 14:26:41 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECT_HPP
# define RECT_HPP

# include "Vec.hpp"

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
	virtual ~Rect(void);

	T			left;
	T			top;
	T			right;
	T			bottom;

/*
** Bounds
*/
	T			getWidth(void) const;
	T			getHeight(void) const;

	/*
	** Move the rect and keep it's size
	*/
	void		setPos(Vec2<T> pos);

	void		setSize(Vec2<T> size);

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
** Operators
*/
	Rect<T>		&operator=(Rect<T> const &rhs);

	bool		operator==(Rect<T> const &rhs) const;

protected:
private:
};

};

# include "templates/Rect.tpp"

#endif
