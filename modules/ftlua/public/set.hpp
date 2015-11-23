// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   set.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/22 11:52:23 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/23 11:56:55 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_SET_HPP
# define FTLUA_SET_HPP

# include "ftlua/push.hpp"

namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// ftlua::set in tab, tab's keys provided
// 		Restores stack as it was before call
template <bool USELUAERR = false
		  , class ...ARGS, class TK, class TV>
void        set(
	lua_State *l
	, KeysWrapper<ARGS...> const &tabGlobalKeys
	, TK const &key
	, TV const &val)
{
	ftlua::multiPush<USELUAERR>(l, tabGlobalKeys, key, val);
	if (!lua_istable(l, -3))
	{
		//from set
		//KeysWrapper to string
		//FTLUA_STACKASSERT(PRED,
		if (USELUAERR)
			luaL_error(l, "ftlua::set table missing");
		else
			throw std::runtime_error(
				ft::f("ftlua::set table missing"));
	}
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
	if (!lua_istable(l, tabIndex))
	{
		//from set
		//KeysWrapper to string
		//FTLUA_STACKASSERT(PRED,
		if (USELUAERR)
			luaL_error(l, "ftlua::set table missing");
		else
			throw std::runtime_error(
				ft::f("ftlua::set table missing"));
	}
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
