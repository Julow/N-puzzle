// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   type_traits.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 14:36:46 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/26 12:46:24 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FT_TYPE_TRAITS_HPP
# define FT_TYPE_TRAITS_HPP

# include <type_traits>
# include <ostream>

#define ISSAME(A, B) std::is_same<A, B>::value
#define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr

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

template<typename T>
struct has_iterator
{
private:
	typedef char			yes_t[1];
	typedef char			no_t[2];

	template<typename C>
	static yes_t			&test(typename C::const_iterator*);
	template<typename C>
	static no_t				&test(...);

	using ItVal = decltype(test<T>(nullptr));
public:
	static constexpr bool	value = ISSAME(ItVal, yes_t&);

};

template<typename T >
class has_begin
{
	typedef char			yes_t[1];
	typedef char			no_t[2];

	template <class C
			  , class WishedFun = typename C::const_iterator (C::*)() const
			  , class BeginFun = decltype(static_cast<WishedFun>(&C::begin))
			  , OK_IF(ISSAME(WishedFun, BeginFun))
			  >
	static yes_t			&test(void *);

	template <class C>
	static no_t				&test(...);

	using BeginVal = decltype(test<T>(nullptr));

public:
	static constexpr bool	value = ISSAME(BeginVal, yes_t&);

};

template<typename T >
class has_end
{
	typedef char			yes_t[1];
	typedef char			no_t[2];

	template <class C
			  , class WishedFun = typename C::const_iterator (C::*)() const
			  , class EndFun = decltype(static_cast<WishedFun>(&C::end))
			  , OK_IF(ISSAME(WishedFun, EndFun))
			  >
	static yes_t			&test(void *);

	template <class C>
	static no_t				&test(...);

	using EndVal = decltype(test<T>(nullptr));

public:
	static constexpr bool	value = ISSAME(EndVal, yes_t&);

};

template<typename T>
struct is_container : std::integral_constant<
	bool, has_iterator<T>::value
	&& has_begin<T>::value && has_end<T>::value>
{};


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FT //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

# undef OK_IF
# undef ISSAME

#endif /* ************************************************ FT_TYPE_TRAITS_HPP */
