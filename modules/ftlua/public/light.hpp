// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   light.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/22 11:58:41 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/22 11:59:42 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_LIGHT_HPP
# define FTLUA_LIGHT_HPP

# include "ftlua/push.hpp"

namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


inline void					*light(void *ptr)
{
	return ptr;
}

inline int					pushLight(lua_State *l, void *ptr)
{
	lua_pushlightuserdata(l, ptr);
	return 1;
}

inline KeysWrapper<void*>	lightKey(void *ptr)
{
	return make_keys(ptr);
}

inline int					pushLightKey(lua_State *l, void *ptr)
{
	return ftlua::push(l, make_keys(ptr));
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#endif
