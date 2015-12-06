// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   conversions.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/02 17:43:22 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/06 13:06:04 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_CONVERTER_HPP
# define FTLUA_CONVERTER_HPP

# include "ft/type_traits.hpp"
# include "liblua/lua.hpp"


namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


# define ISSAME(A, B) std::is_same<A, B>::value
# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISCONV(A, B) std::is_convertible<A, B>::value

# define ISBASE(A, B) std::is_base_of<A, B>::value
# define ISPTR(A) std::is_pointer<A>::value
# define DELPTR(T) typename std::remove_pointer<T>::type

FT_DEFINE_TYPETRAIT_TEST(
	has_size
	, class TT = typename C::ftlua_size
	, class T1 = typename TT::value_type
	, OK_IF(ISSAME(T1, unsigned int))
	, unsigned int T2 = TT::value
	, OK_IF((T2 > 0))
	);

FT_DEFINE_TYPETRAIT_TEST(
	has_push
	, class WishedFun = void (C::*)(lua_State*, std::function<void(std::string)>)
	, class Fun = decltype(static_cast<WishedFun>(&C::ftlua_push))
	, OK_IF(ISSAME(Fun, WishedFun))
	);

FT_DEFINE_TYPETRAIT_TEST(
	has_constpush
	, class WishedFun = void (C::*)(lua_State*, std::function<void(std::string)>) const
	, class Fun = decltype(static_cast<WishedFun>(&C::ftlua_push))
	, OK_IF(ISSAME(Fun, WishedFun))
	);

FT_DEFINE_TYPETRAIT_TEST(
	has_pop
	, class WishedFun = C (*)(lua_State*, int, std::function<void(std::string)>)
	, class Fun = decltype(static_cast<WishedFun>(&C::ftlua_pop))
	, OK_IF(ISSAME(Fun, WishedFun))
	);

FT_DEFINE_TYPETRAIT_TEST(
	has_ptrpop
	, class Fun = decltype(&C::ftlua_pop)
	, class Ret = typename ft::return_type<Fun>::type
	, OK_IF(ISPTR(Ret))
	, OK_IF(ISBASE(DELPTR(Ret), C))
	, class WishedFun = Ret (*)(lua_State*, int, std::function<void(std::string)>)
	, OK_IF(ISSAME(Fun, WishedFun))
	);


}; // ~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


# undef ISSAME
# undef OK_IF
# undef ISCONV
# undef ISBASE
# undef ISPTR
# undef ISCONV


#endif /* *********************************************** FTLUA_CONVERTER_HPP */
