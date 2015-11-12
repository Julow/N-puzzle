// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   push_utils.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/13 07:41:25 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/12 21:03:22 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftlua/ftlua.hpp"
#include "ft/assert.hpp"

namespace ftlua
{

void		pushUtils(lua_State *l)
{
	int		err;

	err = luaL_dofile(l, (RES_PATH "/utils.lua"));
	FTASSERT(err == LUA_OK);
	return ;
}

};
