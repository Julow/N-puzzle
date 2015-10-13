// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ftlua_caller.tpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/13 15:44:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/13 17:25:50 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

namespace ftlua
{

template<size_t N, typename ARG, typename ...ARGS>
void			_call(lua_State *l, ARG arg, ARGS ...args)
{
	push(l, arg);
	_call<N + 1>(l, args...);
}

template<size_t N>
void			_call(lua_State *l)
{
	lua_call(l, N, 0);
}

template<size_t N, typename ...ARGS>
void			call(lua_State *l, ARGS ...args)
{
	_call<N>(l, args...);
}

template<typename ...ARGS>
void			call(lua_State *l, std::string const &name, ARGS ...args)
{
	push(l, name);
	if (lua_gettable(l, -2) != LUA_TFUNCTION)
		luaL_error(l, "Lua missing function");
	_call<0>(l, args...);
}

};
