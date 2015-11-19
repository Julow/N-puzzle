// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Vec4.tpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/05 14:45:47 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/19 13:29:09 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <type_traits>

namespace ft
{

template <typename T>
constexpr Vec4<T>::Vec4(void) :
	x(0),
	y(0),
	z(0),
	w(0)
{
}

template <typename T>
constexpr Vec4<T>::Vec4(Vec2<T> const &src, T z, T w) :
	x(src.x),
	y(src.y),
	z(z),
	w(w)
{
}

template <typename T>
constexpr Vec4<T>::Vec4(T x, Vec2<T> const &src, T w) :
	x(x),
	y(src.x),
	z(src.y),
	w(w)
{
}

template <typename T>
constexpr Vec4<T>::Vec4(T x, T y, Vec2<T> const &src) :
	x(x),
	y(y),
	z(src.x),
	w(src.y)
{
}

template <typename T>
constexpr Vec4<T>::Vec4(Vec2<T> const &a, Vec2<T> const &b) :
	x(a.x),
	y(a.y),
	z(b.x),
	w(b.y)
{
}

template <typename T>
constexpr Vec4<T>::Vec4(Vec3<T> const &src, T w) :
	x(src.x),
	y(src.y),
	z(src.z),
	w(w)
{
}

template <typename T>
constexpr Vec4<T>::Vec4(T x, Vec3<T> const &src) :
	x(x),
	y(src.x),
	z(src.y),
	w(src.z)
{
}

template <typename T>
constexpr Vec4<T>::Vec4(Vec4<T> const &src) :
	x(src.x),
	y(src.y),
	z(src.z),
	w(src.w)
{
}

template <typename T>
constexpr Vec4<T>::Vec4(T v) :
	x(v),
	y(v),
	z(v),
	w(v)
{
}

template <typename T>
constexpr Vec4<T>::Vec4(T x, T y, T z, T w) :
	x(x),
	y(y),
	z(z),
	w(w)
{
}

template <typename T>
Vec4<T>::~Vec4(void)
{
}

template <typename T>
constexpr Vec4<T>	&Vec4<T>::operator=(Vec4<T> const &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
	return (*this);
}

template <typename T>
constexpr bool		Vec4<T>::operator==(Vec4<T> const &rhs) const
{
	return (rhs.x == x && rhs.y == y && rhs.z == z && rhs.w == w);
}

# define DECLARE_OPERATOR(OP) \
template <typename T>													\
constexpr Vec4<T>	&Vec4<T>::operator OP##=(Vec4<T> const &rhs)		\
{																		\
	x OP##= rhs.x;														\
	y OP##= rhs.y;														\
	z OP##= rhs.z;														\
	w OP##= rhs.w;														\
	return (*this);														\
}																		\
template <typename T>													\
constexpr Vec4<T>	&Vec4<T>::operator OP##=(T v)						\
{																		\
	x OP##= v;															\
	y OP##= v;															\
	z OP##= v;															\
	w OP##= v;															\
	return (*this);														\
}																		\
template <typename T>													\
constexpr Vec4<T>	Vec4<T>::operator OP(Vec4<T> const &rhs) const		\
{																		\
	return (Vec4<T>(x OP rhs.x, y OP rhs.y, z OP rhs.z, w OP rhs.w));	\
}																		\
template <typename T>													\
constexpr Vec4<T>	Vec4<T>::operator OP(T v) const						\
{																		\
	return (Vec4<T>(x OP v, y OP v, z OP v, w OP v));					\
}

DECLARE_OPERATOR(+)
DECLARE_OPERATOR(-)
DECLARE_OPERATOR(*)
DECLARE_OPERATOR(/)

# undef DECLARE_OPERATOR

template<typename T>
template<typename C>
constexpr Vec4<T>::operator Vec4<C>(void) const
{
	return (ft::make_vec(
		static_cast<C>(x),
		static_cast<C>(y),
		static_cast<C>(z),
		static_cast<C>(w)
	));
}

template <typename T>
constexpr Vec4<T>	make_vec(T x, T y, T z, T w)
{
	return (Vec4<T>(x, y, z, w));
}

template <typename T>
constexpr Vec4<T>	make_vec(Vec2<T> const &src, T z, T w)
{
	return (Vec4<T>(src, z, w));
}

template <typename T>
constexpr Vec4<T>	make_vec(T x, Vec2<T> const &src, T w)
{
	return (Vec4<T>(x, src, w));
}

template <typename T>
constexpr Vec4<T>	make_vec(T x, T y, Vec2<T> const &src)
{
	return (Vec4<T>(x, y, src));
}

template <typename T>
constexpr Vec4<T>	make_vec(Vec2<T> const &a, Vec2<T> const &b)
{
	return (Vec4<T>(a, b));
}

template <typename T>
constexpr Vec4<T>	make_vec(Vec3<T> const &src, T w)
{
	return (Vec4<T>(src, w));
}

template <typename T>
constexpr Vec4<T>	make_vec(T x, Vec3<T> const &src)
{
	return (Vec4<T>(x, src));
}

static_assert(!std::is_polymorphic<Vec4<int>>(), "It shouldn't be!");

};
