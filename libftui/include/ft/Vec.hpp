// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Vec.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 15:04:00 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/12 18:52:56 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef VEC_HPP
# define VEC_HPP

namespace ft
{

/*
** Vec2 (x, y)
** Vec3 (x, y, z)
** Vec4 (x, y, z, w)
** -
** Support a lot of constructor and operator
** -
** TODO: constexpr
*/

# define _OPERATORS(TYPE,OP) \
	constexpr TYPE<T>	&operator OP##=(TYPE<T> const &rhs);	\
	constexpr TYPE<T>	&operator OP##=(T v);					\
	constexpr TYPE<T>	operator OP(TYPE<T> const &rhs) const;	\
	constexpr TYPE<T>	operator OP(T v) const;
# define OPERATORS(TYPE) \
	_OPERATORS(TYPE, +)								\
	_OPERATORS(TYPE, -)								\
	_OPERATORS(TYPE, *)								\
	_OPERATORS(TYPE, /)

template <typename T>
class	Vec2
{
public:
	constexpr Vec2(void);
	constexpr Vec2(Vec2<T> const &src);
	constexpr Vec2(T v);
	constexpr Vec2(T x, T y);
	~Vec2(void);

	T			x;
	T			y;

	constexpr Vec2<T>	&operator=(Vec2<T> const &rhs);

	OPERATORS(Vec2)

	constexpr bool		operator==(Vec2<T> const &rhs) const;

protected:
private:
};

template <typename T>
constexpr Vec2<T>	make_vec(T x, T y);

template <typename T>
class	Vec3
{
public:
	constexpr Vec3(void);
	constexpr Vec3(Vec2<T> const &src, T z);
	constexpr Vec3(T x, Vec2<T> const &src);
	constexpr Vec3(Vec3<T> const &src);
	constexpr Vec3(T v);
	constexpr Vec3(T x, T y, T z);
	~Vec3(void);

	T			x;
	T			y;
	T			z;

	constexpr Vec3<T>	&operator=(Vec3<T> const &rhs);

	OPERATORS(Vec3)

	constexpr bool		operator==(Vec3<T> const &rhs) const;

protected:
private:
};

template <typename T>
constexpr Vec3<T>	make_vec(T x, T y, T z);
template <typename T>
constexpr Vec3<T>	make_vec(Vec2<T> const &src, T z);
template <typename T>
constexpr Vec3<T>	make_vec(T x, Vec2<T> const &src);

template <typename T>
class	Vec4
{
public:
	constexpr Vec4(void);
	constexpr Vec4(Vec2<T> const &src, T z, T w);
	constexpr Vec4(T x, Vec2<T> const &src, T w);
	constexpr Vec4(T x, T y, Vec2<T> const &src);
	constexpr Vec4(Vec2<T> const &a, Vec2<T> const &b);
	constexpr Vec4(Vec3<T> const &src, T w);
	constexpr Vec4(T x, Vec3<T> const &src);
	constexpr Vec4(Vec4<T> const &src);
	constexpr Vec4(T v);
	constexpr Vec4(T x, T y, T z, T w);
	~Vec4(void);

	T			x;
	T			y;
	T			z;
	T			w;

	constexpr Vec4<T>	&operator=(Vec4<T> const &rhs);

	OPERATORS(Vec4)

	constexpr bool		operator==(Vec4<T> const &rhs) const;

protected:
private:
};

template <typename T>
constexpr Vec4<T>	make_vec(T x, T y, T z, T w);
template <typename T>
constexpr Vec4<T>	make_vec(Vec2<T> const &src, T z, T w);
template <typename T>
constexpr Vec4<T>	make_vec(T x, Vec2<T> const &src, T w);
template <typename T>
constexpr Vec4<T>	make_vec(T x, T y, Vec2<T> const &src);
template <typename T>
constexpr Vec4<T>	make_vec(Vec2<T> const &a, Vec2<T> const &b);
template <typename T>
constexpr Vec4<T>	make_vec(Vec3<T> const &src, T w);
template <typename T>
constexpr Vec4<T>	make_vec(T x, Vec3<T> const &src);

# undef _OPERATORS
# undef OPERATORS

};

# include "ft/templates/Vec2.tpp"
# include "ft/templates/Vec3.tpp"
# include "ft/templates/Vec4.tpp"

#endif
