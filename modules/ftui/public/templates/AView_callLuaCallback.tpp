// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_callLuaCallback.tpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/13 14:01:22 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/19 18:34:52 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

namespace ftui
{

/*
** Call a lua callback from callback id
*/
template<typename ...ARGS>
bool		AView::callLuaCallback(lua_State *l, LuaCallback id, ARGS const &...args)
{
	return (callLuaCallback(l, static_cast<uint32_t>(id), args...));
}


template<typename ...ARGS>
bool		AView::callLuaCallback(lua_State *l, uint32_t id, ARGS const &...args)
{
	if (!(_luaCallbacks & (1 << id)))
		return false;
	if (ftlua::pcallGlobalMethod(
			l, 0, ftlua::make_keys(this), ftlua::make_keys(id), args...))
		throw std::runtime_error(ft::f("Lua: %", luaL_checkstring(l, -1)));
	return true;
}

};
