/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 15:04:00 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/05 14:26:29 by jaguillo         ###   ########.fr       */
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

template <typename T>
class	Vec2
{
public:
	Vec2(void) : x(0), y(0) {}
	Vec2(Vec2<T> const &src) : x(src.x), y(src.y) {}
	Vec2(T v) : x(v), y(v) {}
	Vec2(T x, T y) : x(x), y(y) {}
	virtual ~Vec2(void){}

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
	Vec3(Vec2<T> const &src, T z) : x(src.x), y(src.y), z(z) {}
	Vec3(Vec3<T> const &src) : x(src.x), y(src.y), z(src.z) {}
	Vec3(T v) : x(v), y(v), z(v) {}
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
	virtual ~Vec3(void){}

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

template <typename T>
class	Vec4
{
public:
	Vec4(void) : x(0), y(0), z(0), w(0) {}
	Vec4(Vec2<T> const &src, T z, T w) : x(src.x), y(src.y), z(z), w(w) {}
	Vec4(Vec3<T> const &src, T w) : x(src.x), y(src.y), z(src.z), w(w) {}
	Vec4(Vec4<T> const &src) : x(src.x), y(src.y), z(src.z), w(src.w) {}
	Vec4(T v) : x(v), y(v), z(v), w(v) {}
	Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	virtual ~Vec4(void){}

	T			x;
	T			y;
	T			z;
	T			w;

	Vec4<T>		&operator=(Vec4<T> const &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return (*this);
	}

# define DECLARE_OPERATOR(OP) \
	Vec4<T>		&operator OP##=(Vec4<T> const &rhs)							\
	{																		\
		x OP##= rhs.x;														\
		y OP##= rhs.y;														\
		z OP##= rhs.z;														\
		w OP##= rhs.w;														\
		return (*this);														\
	}																		\
	Vec4<T>		&operator OP##=(T v)										\
	{																		\
		x OP##= v;															\
		y OP##= v;															\
		z OP##= v;															\
		w OP##= v;															\
		return (*this);														\
	}																		\
	Vec4<T>		operator OP(Vec4<T> const &rhs) const						\
	{																		\
		return (Vec4<T>(x OP rhs.x, y OP rhs.y, z OP rhs.z, w OP rhs.w));	\
	}																		\
	Vec4<T>		operator OP(T v) const										\
	{																		\
		return (Vec4<T>(x OP v, y OP v, z OP v, w OP v));					\
	}
	DECLARE_OPERATOR(+)
	DECLARE_OPERATOR(-)
	DECLARE_OPERATOR(*)
	DECLARE_OPERATOR(/)
# undef DECLARE_OPERATOR

	bool		operator==(Vec4<T> const &rhs) const
	{
		return (rhs.x == x && rhs.y == y && rhs.z == z && rhs.w == w);
	}

protected:
private:
};

};

#endif
