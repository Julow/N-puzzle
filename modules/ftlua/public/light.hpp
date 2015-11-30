// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   light.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/22 11:58:41 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/30 18:42:45 by ngoguey          ###   ########.fr       //
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

template <int Relative = 0>
KeysWrapper<Relative, void*>	lightKey(void *ptr)
{
	return ftlua::makeKeys<Relative>(ptr);
}

template <int Relative = 0>
int							pushLightKey(lua_State *l, void *ptr)
{
	return ftlua::push(l, ftlua::makeKeys<Relative>(ptr));
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#endif
