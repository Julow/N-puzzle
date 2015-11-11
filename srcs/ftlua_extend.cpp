// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ftlua_extend.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/11 16:25:11 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/11 16:26:26 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftlua/ftlua.hpp"
#include "ft/assert.hpp"
#include "Grid.hpp"

namespace ftlua
{

int				pushgrid(lua_State *l, Grid const &gr)
{
	int const	w = gr.getSize();

	lua_createtable(l, w * w, 0);
	for (int i = 0; i < w * w; i++)
	{
		lua_pushinteger(l, i);
		lua_pushinteger(l, gr.get(i % w, i / w));
		lua_settable(l, -3);
	}
	return (1);
}

};
