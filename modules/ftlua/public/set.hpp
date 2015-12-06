// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   set.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/22 11:52:23 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/06 13:11:14 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_SET_HPP
# define FTLUA_SET_HPP

# include "ftlua/push.hpp"
# include "ftlua/stackassert.hpp"


namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// Function:		ftlua::set
// Overload:		Table from global
// Stack effect:	Unchanged
// Lua effect:		"local t = _G[tabGlobalKeys];
//					 t[key] = val;"
template <bool USELUAERR = false
		  , class ...ARGS, class TK, class TV>
void        set(
	lua_State *l
	, KeysWrapper<0, ARGS...> const &tabGlobalKeys
	, TK const &key
	, TV const &val)
{
	ftlua::multiPush<USELUAERR>(l, tabGlobalKeys, key, val);
	FTLUA_STACKASSERT(
		l, lua_istable(l, -3), USELUAERR
		, ft::f("ftlua::set(KeysWrapper<%>, %, %)."
				, ft::tupleToString(tabGlobalKeys.tup)
				, ft::valToString(key)
				, ft::valToString(val))
		, ft::f("Table was expected as set target.")
		);
	lua_settable(l, -3);
	lua_pop(l, 1);
	return ;
}

// Function:		ftlua::set
// Overload:		Global
// Stack effect:	Unchanged
// Lua effect:		"_G[key] = val;"
template <bool USELUAERR = false
		  , class TK, class TV>
void        set(
	lua_State *l
	, TK const &key
	, TV const &val)
{
	lua_pushglobaltable(l);
	ftlua::multiPush<USELUAERR>(l, key, val);
	lua_settable(l, -3);
	lua_pop(l, 1);
	return ;
}

// Function:		ftlua::set
// Overload:		Table from stack
// Stack effect:	Unchanged
// Lua effect:		"local t = {STACK@tabIndex};
//					 t[key] = val;"
template <bool USELUAERR = false
		  , class TK, class TV>
void        set(
	lua_State *l
	, int tabIndex
	, TK const &key
	, TV const &val)
{
	FTLUA_STACKASSERT(
		l, lua_istable(l, tabIndex), USELUAERR
		, ft::f("ftlua::set(%, %, %)."
				, tabIndex
				, ft::valToString(key)
				, ft::valToString(val))
		, ft::f("Table was expected after as set target.")
		);
	ftlua::multiPush<USELUAERR>(l, key, val);
	if (tabIndex < 0)
		lua_settable(l, tabIndex - 2);
	else
		lua_settable(l, tabIndex);
	return ;
}


}; // ~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


#endif
