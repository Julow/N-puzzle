/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 15:04:00 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/30 17:59:02 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_HPP
# define VEC_HPP

# include "libftui.h"

namespace ftui
{

template <typename T>
class	Vec2
{
public:
	Vec2(void) : x(0), y(0) {}
	Vec2(Vec2<T> const &src) : x(src.x), y(src.y) {}
	Vec2(T v) : x(v), y(v) {}
	Vec2(T x, T y) : x(x), y(y) {}
	virtual ~Vec2(void);

	T			x;
	T			y;

	Vec2<T>		&operator=(Vec2<T> const &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return (*this);
	}

# define DECLARE_OPERATOR(OP) \
	Vec2<T>		&operator OP##=(Vec2<T> const &rhs)		\
	{													\
		x OP##= rhs.x;									\
		y OP##= rhs.y;									\
		return (*this);									\
	}													\
	Vec2<T>		&operator OP##=(T v)					\
	{													\
		x OP##= v;										\
		y OP##= v;										\
		return (*this);									\
	}													\
	Vec2<T>		operator OP(Vec2<T> const &rhs) const	\
	{													\
		return (Vec2<T>(x OP rhs.x, y OP rhs.y));		\
	}													\
	Vec2<T>		operator OP(T v) const					\
	{													\
		return (Vec2<T>(x OP v, y OP v));				\
	}
	DECLARE_OPERATOR(+)
	DECLARE_OPERATOR(-)
	DECLARE_OPERATOR(*)
	DECLARE_OPERATOR(/)
# undef DECLARE_OPERATOR

	bool		operator==(Vec2<T> const &rhs) const
	{
		return (rhs.x == x && rhs.y == y);
	}

protected:
private:
};

template <typename T>
class	Vec3
{
public:
	Vec3(void) : x(0), y(0), z(0) {}
	Vec3(Vec3<T> const &src) : x(src.x), y(src.y), z(src.z) {}
	Vec3(Vec2<T> const &src, T z) : x(src.x), y(src.y), z(z) {}
	Vec3(T v) : x(v), y(v), z(v) {}
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
	virtual ~Vec3(void);

	T			x;
	T			y;
	T			z;

	Vec3<T>		&operator=(Vec3<T> const &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return (*this);
	}

# define DECLARE_OPERATOR(OP) \
	Vec3<T>		&operator OP##=(Vec3<T> const &rhs)				\
	{															\
		x OP##= rhs.x;											\
		y OP##= rhs.y;											\
		z OP##= rhs.z;											\
		return (*this);											\
	}															\
	Vec3<T>		&operator OP##=(T v)							\
	{															\
		x OP##= v;												\
		y OP##= v;												\
		z OP##= v;												\
		return (*this);											\
	}															\
	Vec3<T>		operator OP(Vec3<T> const &rhs) const			\
	{															\
		return (Vec3<T>(x OP rhs.x, y OP rhs.y, z OP rhs.z));	\
	}															\
	Vec3<T>		operator OP(T v) const							\
	{															\
		return (Vec3<T>(x OP v, y OP v, z OP v));				\
	}
	DECLARE_OPERATOR(+)
	DECLARE_OPERATOR(-)
	DECLARE_OPERATOR(*)
	DECLARE_OPERATOR(/)
# undef DECLARE_OPERATOR

	bool		operator==(Vec3<T> const &rhs) const
	{
		return (rhs.x == x && rhs.y == y && rhs.z == z);
	}

protected:
private:
};

};

#endif
