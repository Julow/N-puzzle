// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   size.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/02 18:23:45 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/05 12:29:37 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_SIZE_HPP
# define FTLUA_SIZE_HPP

# include <type_traits>

# include "ftlua/types.hpp"

namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <class, bool>
struct size;

template <class T>
struct size<T, false> : std::integral_constant<unsigned int, 1>
{};

template <class T>
struct size<T, true>
{
	static constexpr unsigned int	value = typename T::ftlua_size();
};

template <class T1>
struct size<ft::Vec2<T1>, false> : std::integral_constant<unsigned int, 2>
{};

template <class T1>
struct size<ft::Vec3<T1>, false> : std::integral_constant<unsigned int, 3>
{};

template <class T1>
struct size<ft::Vec4<T1>, false> : std::integral_constant<unsigned int, 4>
{};


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <class T>
struct size : std::integral_constant<
	unsigned int, internal::size<T, ftlua::has_size<T>::value >::value >
{};


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
#endif /* ********************************************************** SIZE_HPP */
