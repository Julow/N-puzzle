// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   type_traits.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 14:36:46 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/23 16:03:39 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FT_TYPE_TRAITS_HPP
# define FT_TYPE_TRAITS_HPP

# include <type_traits>
# include <ostream>

namespace ft // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

namespace dont_drool // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

template <class _CharT, class _Traits, class T>
int		&operator<<(std::basic_ostream<_CharT, _Traits>&, const T&);

template<typename T>
struct is_printable
{
	using Ret = decltype((*(std::ostream*)(0x0)) << (*(T*)(0x0)));

	static constexpr bool	value = std::is_same<Ret, std::ostream&>::value
								|| std::is_convertible<T, std::string>::value;
};
}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE DONT_DROOL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

template<typename T>
struct is_printable
{
	static constexpr bool	value = dont_drool::is_printable<T>::value;
};

}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FT //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


#endif /* ************************************************ FT_TYPE_TRAITS_HPP */
