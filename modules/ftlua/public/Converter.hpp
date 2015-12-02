// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Converter.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/21 10:27:37 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/02 13:41:47 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_CONVERTER_HPP
# define FTLUA_CONVERTER_HPP

# include <type_traits>
# include "liblua/lua.hpp"


namespace ftlua // ========================================================== //
{


#define ISSAME(A, B) std::is_same<A, B>::value
#define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr

template <typename T>
class has_size
{
	typedef char			yes_t[1];
	typedef char			no_t[2];

	template<typename C
			 , class TT = typename C::ftlua_size
			 , class T1 = typename TT::value_type
			 , OK_IF(ISSAME(T1, unsigned int))
			 , unsigned int T2 = TT::value
			 , OK_IF((T2 > 0))
		>
	static yes_t			&test(void *);
	template<typename C>
	static no_t				&test(...);

	using TestRetType = decltype(test<T>(nullptr));
public:
	static constexpr bool	value = ISSAME(TestRetType, yes_t&);
};


template<typename T>
class has_push
{
	typedef char			yes_t[1];
	typedef char			no_t[2];

	template <class C
			  , class WishedFun = bool (C::*)(lua_State*)
			  , class Fun = decltype(static_cast<WishedFun>(&C::ftlua_push))
			  , OK_IF(ISSAME(Fun, WishedFun))
			  >
	static yes_t			&test(void *);

	template <class C>
	static no_t				&test(...);

	using TestRetType = decltype(test<T>(nullptr));

public:
	static constexpr bool	value = ISSAME(TestRetType, yes_t&);

};

// template<typename T>
// class has_constpush
// {
// 	typedef char			yes_t[1];
// 	typedef char			no_t[2];

// 	template <class C
// 			  , class WishedFun = typename bool (C::*)(lua_State*) const
// 			  , class Fun = decltype(static_cast<WishedFun>(&C::ftlua_push))
// 			  , OK_IF(ISSAME(Fun, BeginFun))
// 			  >
// 	static yes_t			&test(void *);

// 	template <class C>
// 	static no_t				&test(...);

// 	using TestRetType = decltype(test<T>(nullptr));

// public:
// 	static constexpr bool	value = ISSAME(TestRetType, yes_t&);

// };


template<typename T
		 , OK_IF(!std::is_void<T>::value)>
class Converter
{
public:

	/* CONSTRUCTION ***************** */
	typedef int				(*push_t)(lua_State *l, T &);

	Converter(T &v, push_t p) : _v(v), _p(p) {}
	Converter(Converter const &src) : _v(src._v), _p(src._p) {}
	~Converter() {}

	Converter() = delete;
	Converter				&operator=(Converter &&rhs) = delete;


	/* BEHAVIOUR ******************** */
	template <bool USELUAERR = false>
	int			callPush(lua_State *l)
		{
			return this->_p(l, this->_v);
		}

// private:
	T						&_v;
	push_t					_p;
};

}; // ================================================ END OF NAMESPACE FTLUA //

# undef ISSAME
# undef OK_IF

#endif /* *********************************************** FTLUA_CONVERTER_HPP */
