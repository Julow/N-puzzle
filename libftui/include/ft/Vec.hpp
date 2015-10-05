/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 15:04:00 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/05 17:15:45 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_HPP
# define VEC_HPP

# include "ftui/libftui.hpp"

namespace ft
{

/*
** Vec2 (x, y)
** Vec3 (x, y, z)
** Vec4 (x, y, z, w)
** -
** Support a lot of constructor and operator
*/

# define _OPERATORS(TYPE,OP) \
	TYPE<T>	&operator OP##=(TYPE<T> const &rhs);		\
	TYPE<T>	&operator OP##=(T v);				\
	TYPE<T>	operator OP(TYPE<T> const &rhs) const;		\
	TYPE<T>	operator OP(T v) const;
# define OPERATORS(TYPE) \
	_OPERATORS(TYPE, +)								\
	_OPERATORS(TYPE, -)								\
	_OPERATORS(TYPE, *)								\
	_OPERATORS(TYPE, /)

template <typename T>
class	Vec2
{
public:
	Vec2(void);
	Vec2(Vec2<T> const &src);
	Vec2(T v);
	Vec2(T x, T y);
	virtual ~Vec2(void);

	T			x;
	T			y;

	Vec2<T>		&operator=(Vec2<T> const &rhs);

	OPERATORS(Vec2)

	bool		operator==(Vec2<T> const &rhs) const;

protected:
private:
};

template <typename T>
class	Vec3
{
public:
	Vec3(void);
	Vec3(Vec2<T> const &src, T z);
	Vec3(Vec3<T> const &src);
	Vec3(T v);
	Vec3(T x, T y, T z);
	virtual ~Vec3(void);

	T			x;
	T			y;
	T			z;

	Vec3<T>		&operator=(Vec3<T> const &rhs);

	OPERATORS(Vec3)

	bool		operator==(Vec3<T> const &rhs) const;

protected:
private:
};

template <typename T>
class	Vec4
{
public:
	Vec4(void);
	Vec4(Vec2<T> const &src, T z, T w);
	Vec4(Vec3<T> const &src, T w);
	Vec4(Vec4<T> const &src);
	Vec4(T v);
	Vec4(T x, T y, T z, T w);
	virtual ~Vec4(void);

	T			x;
	T			y;
	T			z;
	T			w;

	Vec4<T>		&operator=(Vec4<T> const &rhs);

	OPERATORS(Vec4)

	bool		operator==(Vec4<T> const &rhs) const;

protected:
private:
};

# undef _OPERATORS
# undef OPERATORS

};

# include "ft/templates/Vec2.tpp"
# include "ft/templates/Vec3.tpp"
# include "ft/templates/Vec4.tpp"

#endif
