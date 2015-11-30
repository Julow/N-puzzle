// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   call.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 17:09:57 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/30 19:18:05 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_CALL_HPP
# define FTLUA_CALL_HPP

# include "ftlua/types.hpp"
# include "ftlua/push.hpp"

namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// Consumes the function
template <typename ...ARGS>
int					pcall(
	lua_State *l, unsigned int nRet, unsigned int nArgsStack
	, ARGS const & ...args)
{
	FTLUA_STACKASSERT(
		l, lua_isfunction(l, -nArgsStack - 1), false
		, ft::f("ftlua::pcall(%, %, %)."
				, nRet, nArgsStack, ft::variadicToString(args...))
		, ft::f("Function was expected at index.")
		);
	return lua_pcall(l, multiPush(l, args...) + nArgsStack, nRet, 0);
}

// Consumes the table
template <typename ...ARGS, typename ...FKEYS>
int					pcallMethod(
	lua_State *l, unsigned int nRet
	, KeysWrapper< (-1), FKEYS...> const &methodTabKeys
	, ARGS const & ...args)
{
	//											[]
	push(l, methodTabKeys);					//	f	[]
	FTLUA_STACKASSERT(
		l, lua_isfunction(l, -1), false
		, ft::f("ftlua::pcall(%, KeysWrapper<%>, %)."
				, nRet
				, ft::tupleToString(methodTabKeys.tup)
				, ft::variadicToString(args...))
		, ft::f("Function not found in table.")
		);
	lua_pushvalue(l, -2);					//	[]	f	[]
	lua_remove(l, -3);						//	[]	f
	return lua_pcall(l, multiPush(l, args...) + 1, nRet, 0);
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#endif /* ********************************************************** CALL_HPP */
