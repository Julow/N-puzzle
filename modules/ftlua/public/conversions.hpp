// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   conversions.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/02 17:43:22 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/05 11:04:50 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_CONVERTER_HPP
# define FTLUA_CONVERTER_HPP

# include "ft/type_traits.hpp"
# include "liblua/lua.hpp"

namespace ftlua // ========================================================== //
{

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

FT_DEFINE_TYPETRAIT_TEST(
	is_panicfun
	, size_t N = ft::nfun_args<C>::value
	, OK_IF(N == 3)
	, class Last = typename ft::fun_arg<2, C>::type
	, OK_IF(ISSAME(Last, std::function<void(std::string)>))
	// , class ArgsTup = typename ft::args_tup<C>::type
	// , size_t TupSize = std::tuple_size<ArgsTup>::value
	// , class LastArg = typename std::tuple_element<TupSize - 1, ArgsTup>::type
	// , OK_IF(IS_SAME)
	);

// template <typename T>
// class has_panicpush
// {
// 	typedef char            yes_t[1];
// 	typedef char            no_t[2];

// 	template<typename C, __VA_ARGS__>
// 		static yes_t        &test(void *);
// 	template<typename C>
// 		static no_t         &test(...);

// 	using TestRetType = decltype(test<T>(nullptr));
// public:

// 	template <typename U>
// 	static constexpr bool	tester()

// 	static constexpr bool   value = ISSAME(TestRetType, yes_t&);
// }

}; // ================================================ END OF NAMESPACE FTLUA //

# undef ISSAME
# undef OK_IF
# undef ISCONV
# undef ISBASE
# undef ISPTR
# undef ISCONV


#endif /* *********************************************** FTLUA_CONVERTER_HPP */
