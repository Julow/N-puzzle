// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Vec2.tpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/05 14:45:51 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/19 13:31:17 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <type_traits>

namespace ft
{

template <typename T>
constexpr Vec2<T>::Vec2(void) :
	x(0),
	y(0)
{
}

template <typename T>
constexpr Vec2<T>::Vec2(Vec2<T> const &src) :
	x(src.x),
	y(src.y)
{
}

template <typename T>
constexpr Vec2<T>::Vec2(T v) :
	x(v),
	y(v)
{
}

template <typename T>
constexpr Vec2<T>::Vec2(T x, T y) :
	x(x),
	y(y)
{
}

template <typename T>
Vec2<T>::~Vec2(void)
{
}

template <typename T>
constexpr Vec2<T>	&Vec2<T>::operator=(Vec2<T> const &rhs)
{
	x = rhs.x;
	y = rhs.y;
	return (*this);
}

template <typename T>
constexpr bool		Vec2<T>::operator==(Vec2<T> const &rhs) const
{
	return (rhs.x == x && rhs.y == y);
}

# define DECLARE_OPERATOR(OP) \
template <typename T>													\
constexpr Vec2<T>	&Vec2<T>::operator OP##=(Vec2<T> const &rhs)		\
{																		\
	x OP##= rhs.x;														\
	y OP##= rhs.y;														\
	return (*this);														\
}																		\
template <typename T>													\
constexpr Vec2<T>	&Vec2<T>::operator OP##=(T v)						\
{																		\
	x OP##= v;															\
	y OP##= v;															\
	return (*this);														\
}																		\
template <typename T>													\
constexpr Vec2<T>	Vec2<T>::operator OP(Vec2<T> const &rhs) const		\
{																		\
	return (Vec2<T>(x OP rhs.x, y OP rhs.y));							\
}																		\
template <typename T>													\
constexpr Vec2<T>	Vec2<T>::operator OP(T v) const						\
{																		\
	return (Vec2<T>(x OP v, y OP v));									\
}

DECLARE_OPERATOR(+)
DECLARE_OPERATOR(-)
DECLARE_OPERATOR(*)
DECLARE_OPERATOR(/)

# undef DECLARE_OPERATOR

template<typename T>
template<typename C>
constexpr Vec2<T>::operator Vec2<C>(void) const
{
	return (ft::make_vec(static_cast<C>(x), static_cast<C>(y)));
}

template <typename T>
constexpr Vec2<T>	make_vec(T x, T y)
{
	return (Vec2<T>(x, y));
}

static_assert(!std::is_polymorphic<Vec2<int>>(), "It shouldn't be!");

};
