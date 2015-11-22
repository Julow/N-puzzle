// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   call.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 17:09:57 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/22 10:15:43 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_CALL_HPP
# define FTLUA_CALL_HPP

# include "ftlua/types.hpp"
# include "ftlua/push.hpp"

namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <typename ...ARGS>
int					pcall(
	lua_State *l, unsigned int nRet, unsigned int nArgsStack
	, ARGS const & ...args)
{
	return lua_pcall(
		l, multiPush(l, args...) + nArgsStack, nRet, 0);
}

template <typename ...ARGS, typename ...FKEYS>
int					pcallMethod(
	lua_State *l, unsigned int nRet
	, KeysWrapper<FKEYS...> const &methodTabKeys
	, ARGS const & ...args)
{
	lua_pushvalue(l, -1);				// []	[]
	push<true>(l, methodTabKeys);		// f	[]
	lua_pushvalue(l, -2);				// []	f	[]
	lua_remove(l, -3);					// []	f
	return lua_pcall(l, multiPush(l, args...) + 1, nRet, 0);
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#endif /* ********************************************************** CALL_HPP */
