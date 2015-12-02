// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   size.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/02 18:23:45 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/02 18:57:59 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_SIZE_HPP
# define FTLUA_SIZE_HPP

# include <type_traits>

# include "ftlua/types.hpp"

# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define DELPTR(T) typename std::remove_pointer<T>::type
# define DELREF(T) typename std::remove_reference<T>::type
# define DELCONST(T) typename std::remove_const<T>::type

# define ISSAME(A, B) std::is_same<A, B>::value
# define ISPTR(A) std::is_pointer<A>::value
# define ISREF(A) std::is_reference<A>::value
namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// template <class T
// 		  , OK_IF(ISPTR(T))
// 		  , OK_IF(std::is_arithmetic<DELPTR(T)>::value)>
// constexpr unsigned int	size(void) { return 1; }

// template <class T
// 		  , OK_IF(std::is_arithmetic<T>::value)>
// constexpr unsigned int	size(void) { return 1; }


template <class T, OK_IF(ISSAME(DELCONST(T), void*))>
constexpr unsigned int	size(void) { return 1; }

// struct size<T> : std::integral_constant<unsigned int, 1>
// {};


// template <> struct size<int8_t> : std::integral_constant<unsigned int, 1> {};
// template <> struct size<int16_t> : std::integral_constant<unsigned int, 1> {};
// template <> struct size<int32_t> : std::integral_constant<unsigned int, 1> {};
// template <> struct size<int64_t> : std::integral_constant<unsigned int, 1> {};
// template <> struct size<uint8_t> : std::integral_constant<unsigned int, 1> {};
// template <> struct size<uint16_t> : std::integral_constant<unsigned int, 1> {};
// template <> struct size<uint32_t> : std::integral_constant<unsigned int, 1> {};
// template <> struct size<uint64_t> : std::integral_constant<unsigned int, 1> {};

}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
# undef OK_IF
# undef DELPTR
# undef DELREF
# undef DELCONST
# undef ISSAME
# undef ISPTR
# undef ISREF
#endif /* ********************************************************** SIZE_HPP */
