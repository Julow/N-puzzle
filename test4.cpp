// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   test4.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/26 12:08:05 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/26 12:10:07 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>

#define ISSAME(A, B) std::is_same<A, B>::value
#define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr

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

	using ItVal = decltype(test<T>(0));
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

int							main(void)
{

	std::cout
		<< "beg"
		<< has_begin< std::vector<int> >::value
		<< " end"
		<< has_end< std::vector<int> >::value
		<< " it"
		<< has_iterator< std::vector<int> >::value
		<< " container"
		<< is_container< std::vector<int> >::value
		<<	std::endl;
	std::cout
		<< "beg"
		<< has_begin< int >::value
		<< " end"
		<< has_end< int >::value
		<< " it"
		<< has_iterator< int >::value
		<< " container"
		<< is_container< int >::value
		<<	std::endl;
	return (0);
}
