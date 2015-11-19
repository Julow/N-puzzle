// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   call.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 17:09:57 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/19 18:15:32 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_CALL_HPP
# define FTLUA_CALL_HPP

# include "ftlua/types.hpp"
# include "ftlua/push.hpp"

namespace ftlua // ========================================================== //
{

namespace internal // ======================================================= //
{

inline unsigned int		_pushLoop(lua_State *)
{
	return 0;
}

template<typename HEAD, typename ...TAIL>
unsigned int		_pushLoop(lua_State *l, HEAD const &h, TAIL const & ...t)
{
	return ftlua::push(l, h) + internal::_pushLoop(l, t...);
}

}; // ============================================= END OF NAMESPACE INTERNAL //

template <typename ...ARGS>
int					pcall(
	lua_State *l, unsigned int nRet
	, unsigned int nArgsStack
	, ARGS const & ...args)
{
	return lua_pcall(
		l, internal::_pushLoop(l, args...) + nArgsStack, nRet, 0);
}

template <typename ...ARGS, typename ...FKEYS>
int					pcallTableFun(
	lua_State *l, unsigned int nRet
	, KeysWrapper<FKEYS...> const &funTabKeys
	, ARGS const & ...args)
{
	push<true>(l, funTabKeys);
	return lua_pcall(l, internal::_pushLoop(l, args...), nRet, 0);
}

template <typename ...ARGS, typename ...FKEYS>
int					pcallGlobalFun(
	lua_State *l, unsigned int nRet
	, KeysWrapper<FKEYS...> const &funGlobalKeys
	, ARGS const & ...args)
{
	push(l, funGlobalKeys);
	return lua_pcall(l, internal::_pushLoop(l, args...), nRet, 0);
}

template <typename ...ARGS, typename ...FKEYS>
int					pcallTableMethod(
	lua_State *l, unsigned int nRet
	, KeysWrapper<FKEYS...> const &methodTabKeys
	, ARGS const & ...args)
{
	lua_pushvalue(l, -1);				// []	[]
	push<true>(l, methodTabKeys);			// f	[]
	lua_pushvalue(l, -2);				// []	f	[]
	lua_remove(l, -3);					// []	f
	return lua_pcall(l, internal::_pushLoop(l, args...) + 1, nRet, 0);
}

template <typename ...ARGS, typename ...TKEYS, typename ...FKEYS>
int					pcallGlobalMethod(
	lua_State *l, unsigned int nRet
	, KeysWrapper<TKEYS...> const &tabGlobalKeys
	, KeysWrapper<FKEYS...> const &methodTabKeys
	, ARGS const & ...args)
{
	push(l, tabGlobalKeys);				// []
	lua_pushvalue(l, -1);				// []	[]
	push<true>(l, methodTabKeys);			// f	[]
	lua_pushvalue(l, -2);				// []	f	[]
	lua_remove(l, -3);					// []	f
	return lua_pcall(l, internal::_pushLoop(l, args...) + 1, nRet, 0);
}

}; // ================================================ END OF NAMESPACE FTLUA //

#endif /* ********************************************************** CALL_HPP */
