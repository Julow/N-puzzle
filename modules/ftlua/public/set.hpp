// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   set.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/22 11:52:23 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/30 19:02:10 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_SET_HPP
# define FTLUA_SET_HPP

# include "ftlua/push.hpp"
# include "ftlua/stackassert.hpp"

namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// ftlua::set in tab, tab's keys provided
// 		Restores stack as it was before call
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
		, ft::f("Table was expected after as set target.")
		);
	lua_settable(l, -3);
	lua_pop(l, 1);
	return ;
}

// ftlua::set in _G
// 		Restores stack as it was before call
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

// ftlua::set in tab, tab's stack index provided
//		'index' corresponds to tab's index before ftlua::set's call
//		Restores stack as it was before call
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


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#endif
