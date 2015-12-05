// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   size.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/02 18:23:45 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/05 11:46:20 by ngoguey          ###   ########.fr       //
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
