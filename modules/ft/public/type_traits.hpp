// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   type_traits.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 14:36:46 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/05 12:00:35 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FT_TYPE_TRAITS_HPP
# define FT_TYPE_TRAITS_HPP

# include <type_traits>
# include <ostream>

#define ISSAME(A, B) std::is_same<A, B>::value
#define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr

#define FT_DEFINE_TYPETRAIT_TEST(NAME, ...)								\
	template <typename T>												\
	class NAME															\
	{																	\
		typedef char			yes_t[1];								\
		typedef char			no_t[2];								\
																		\
		template<typename C, __VA_ARGS__>								\
			static yes_t		&test(void *);							\
		template<typename C>											\
			static no_t			&test(...);								\
																		\
		using TestRetType = decltype(test<T>(nullptr));					\
	public:																\
		static constexpr bool	value = ISSAME(TestRetType, yes_t&);	\
	}

#define FT_DEFINE_TYPETRAIT_BOOLCONSTANT(NAME, PRED)	\
	template<typename T>								\
	struct NAME : std::integral_constant<bool, PRED>	\
	{}


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

	static constexpr bool	value =
					std::is_same<Ret, std::ostream&>::value
					|| std::is_convertible<T, std::string>::value;
};
}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE DONT_DROOL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


FT_DEFINE_TYPETRAIT_BOOLCONSTANT(
	is_printable, dont_drool::is_printable<T>::value);

FT_DEFINE_TYPETRAIT_TEST(
	has_iterator
	, class It = typename C::const_iterator
	);

FT_DEFINE_TYPETRAIT_TEST(
	has_begin
	, class WishedFun = typename C::const_iterator (C::*)() const
	, class BeginFun = decltype(static_cast<WishedFun>(&C::begin))
	, OK_IF(ISSAME(WishedFun, BeginFun))
	);

FT_DEFINE_TYPETRAIT_TEST(
	has_end
	, class WishedFun = typename C::const_iterator (C::*)() const
	, class BeginFun = decltype(static_cast<WishedFun>(&C::end))
	, OK_IF(ISSAME(WishedFun, BeginFun))
	);

FT_DEFINE_TYPETRAIT_BOOLCONSTANT(
	is_container
	, has_iterator<T>::value && has_begin<T>::value && has_end<T>::value);

FT_DEFINE_TYPETRAIT_TEST(
	is_complete //TODO: debug
	, OK_IF((sizeof(C) > 0))
	);

template <class F>
struct return_type;//TODO:: overloads for member functions

template <class Ret, class ...Args>
struct return_type<Ret (*)(Args...)>
{
	typedef Ret type;
};

template <class Ret, class ...Args>
struct return_type<Ret (*)(Args..., ...)>
{
	typedef Ret type;
};

template <class F>
struct nfun_args;

template <class Ret, class Head, class ...Args>
struct nfun_args<Ret (*)(Head, Args...)>
	: public std::integral_constant<
	size_t, std::tuple_size<std::tuple<Head, Args...> >::value>
{};

template <size_t I, class F>
struct fun_arg;

template <size_t I, class Ret, class Head, class ...Args>
struct fun_arg<I, Ret (*)(Head, Args...)>
{
	typedef typename std::tuple_element<I, std::tuple<Head, Args...> >::type type;
};


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FT //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
# undef OK_IF
# undef ISSAME
#endif /* ************************************************ FT_TYPE_TRAITS_HPP */
