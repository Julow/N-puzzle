// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_callLuaCallback.tpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/13 14:01:22 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/13 18:38:58 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

namespace ftui
{

/*
** Call a lua callback from callback id
*/
template<typename ...ARGS>
bool		AView::callLuaCallback(lua_State *l, LuaCallback id, ARGS ...args)
{
	return (callLuaCallback(l, static_cast<uint32_t>(id), args...));
}

template<typename ...ARGS>
bool		AView::callLuaCallback(lua_State *l, uint32_t id, ARGS ...args)
{
	if (!(_luaCallbacks & (1 << id)))
		return (false);
	lua_pushglobaltable(l);					// <-	_G
	lua_pushlightuserdata(l, this);			// <-	view_ptr, _G
	if (lua_gettable(l, -2) != LUA_TTABLE)	// <-	view_table, _G
		luaL_error(l, "Lua missing table");
	lua_pushinteger(l, id);					// <-	callback_id, view_table, _G
	if (lua_gettable(l, -2) != LUA_TFUNCTION)	// <-	function, view_table, _G
		luaL_error(l, "Lua missing callback");
	lua_pushvalue(l, -2);					// <-	view_table, function, v, _G
	ftlua::call<1>(l, args...);				// <-	view_table, _G
	lua_pop(l, 2);							// <-	empty
	return (true);
}

};
