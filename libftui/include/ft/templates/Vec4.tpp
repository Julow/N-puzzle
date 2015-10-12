// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Vec4.tpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/05 14:45:47 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/12 15:50:05 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

namespace ft
{

template <typename T>
Vec4<T>::Vec4(void) :
	x(0),
	y(0),
	z(0),
	w(0)
{
}

template <typename T>
Vec4<T>::Vec4(Vec2<T> const &src, T z, T w) :
	x(src.x),
	y(src.y),
	z(z),
	w(w)
{
}

template <typename T>
Vec4<T>::Vec4(Vec3<T> const &src, T w) :
	x(src.x),
	y(src.y),
	z(src.z),
	w(w)
{
}

template <typename T>
Vec4<T>::Vec4(Vec4<T> const &src) :
	x(src.x),
	y(src.y),
	z(src.z),
	w(src.w)
{
}

template <typename T>
Vec4<T>::Vec4(T v) :
	x(v),
	y(v),
	z(v),
	w(v)
{
}

template <typename T>
Vec4<T>::Vec4(T x, T y, T z, T w) :
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
Vec4<T>		&Vec4<T>::operator=(Vec4<T> const &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
	return (*this);
}

template <typename T>
bool		Vec4<T>::operator==(Vec4<T> const &rhs) const
{
	return (rhs.x == x && rhs.y == y && rhs.z == z && rhs.w == w);
}

# define DECLARE_OPERATOR(OP) \
template <typename T>													\
Vec4<T>		&Vec4<T>::operator OP##=(Vec4<T> const &rhs)				\
{																		\
	x OP##= rhs.x;														\
	y OP##= rhs.y;														\
	z OP##= rhs.z;														\
	w OP##= rhs.w;														\
	return (*this);														\
}																		\
template <typename T>													\
Vec4<T>		&Vec4<T>::operator OP##=(T v)								\
{																		\
	x OP##= v;															\
	y OP##= v;															\
	z OP##= v;															\
	w OP##= v;															\
	return (*this);														\
}																		\
template <typename T>													\
Vec4<T>		Vec4<T>::operator OP(Vec4<T> const &rhs) const				\
{																		\
	return (Vec4<T>(x OP rhs.x, y OP rhs.y, z OP rhs.z, w OP rhs.w));	\
}																		\
template <typename T>													\
Vec4<T>		Vec4<T>::operator OP(T v) const								\
{																		\
	return (Vec4<T>(x OP v, y OP v, z OP v, w OP v));					\
}

DECLARE_OPERATOR(+)
DECLARE_OPERATOR(-)
DECLARE_OPERATOR(*)
DECLARE_OPERATOR(/)

# undef DECLARE_OPERATOR

template <typename T>
Vec4<T>		make_vec(T x, T y, T z, T w)
{
	return (Vec4<T>(x, y, z, w));
}

static_assert(!std::is_polymorphic<Vec4<int>>(), "It shouldn't be!");

};
