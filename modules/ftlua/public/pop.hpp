// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   pop.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:16:24 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/02 12:04:58 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_POP_HPP
# define FTLUA_POP_HPP

# include <cstdint>
# include <string>

# include "liblua/lua.hpp"
# include "ft/Vec.hpp"
# include "ft/Rect.hpp"
# include "ft/utils.hpp"
# include "ft/assert.hpp" //debug

# include "ftlua/types.hpp"
# include "ftlua/utils.hpp"


namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
# define DELPTR(T) typename std::remove_pointer<T>::type
# define DELCONST(T) typename std::remove_const<T>::type
# define OK_IFNODEF(PRED) typename std::enable_if<PRED>::type*
# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISPTR(A) std::is_pointer<A>::value
# define ISCONST(A) std::is_const<A>::value
# define ISCONV(A, B) std::is_convertible<A, B>::value
# define ISSAME(A, B) std::is_same<A, B>::value
# define OK_IFSAME(A, B) OK_IF(ISSAME(A, B))

// template <class T, bool LuaErr = true, OK_IFSAME(T, int)>
// T	pop(lua_State *l, int index, bool &noErr, unsigned int &nret)
// {
// 	if (!lua_isinteger(l, index))
// 	{
// 		if (info != nullptr && info->first == true)
// 			}
// 	else if (info != nullptr)
// 		info->second = 1;
// 	return {};
// }

# define DEFINE_POP(TYPE, FUNCSUFFIX)									\
	template <class T, bool LuaErr = true, OK_IFSAME(T, TYPE)>			\
	T	pop(lua_State *l, TYPE index)									\
	{																	\
		FTLUA_STACKASSERT(												\
			l, lua_is##FUNCSUFFIX(l, index), LuaErr						\
			, ft::f("ftlua::pop<%>(%).", index, #TYPE)					\
			, ft::f("Index % should have been an %.", index, #FUNCSUFFIX) \
			);															\
		return lua_to##FUNCSUFFIX(l, index);							\
	}

DEFINE_POP(int8_t, integer)
DEFINE_POP(int, integer)

# undef DEFINE_POP

template <class T, bool LuaErr = true, OK_IFSAME(T, std::string*)>
T	pop(lua_State *l, int index, std::pair<bool, unsigned int> *info = nullptr)
{
	(void)l;
	(void)info;
	(void)index;
	return {};
}

template <class TT, bool LuaErr = true, class T1 = typename TT::value_type
		  , OK_IFSAME(TT, ft::Vec2<T1>)>
TT	pop(lua_State *l, int index, std::pair<bool, unsigned int> *info = nullptr)
{
	(void)l;
	(void)info;
	(void)index;
	return {};
}


template <class T, bool LuaErr = true
		  , OK_IF(ft::is_complete<T>::value)
		  , OK_IF(ISCONV(T, Converter<T>))
		  , OK_IF(std::is_default_constructible<T>::value)
		  >
T	pop(lua_State *l, int index)
{
	(void)l;
	(void)index;
	return {};
}

template <class T, bool LuaErr = true
		  , OK_IF(ft::is_complete<T>::value)
		  , OK_IF(ISCONV(T, Converter<T>))
		  , OK_IF(!std::is_default_constructible<T>::value)
		  >
T	&pop(lua_State *l, int index)
{
	Converter<T>	conv = static_cast< Converter<T> >(*(T*)(0x0));
	std::cout << (void*)&conv._v << std::endl;
	std::cout << (void*)conv._p << std::endl;
	(void)l;
	(void)index;
	return *(T*)(0x0);
}



# undef DELPTR
# undef DELCONST
# undef ISCONV
# undef ISPTR
# undef ISCONST
# undef OK_IF
# undef OK_IFNODEF
# undef ISSAME
# undef OK_IFISSAME

}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
#endif /* *********************************************************** POP_HPP */
