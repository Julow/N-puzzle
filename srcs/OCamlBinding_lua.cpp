// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OCamlBinding_lua.cpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/09 12:49:45 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/09 13:44:38 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "OCamlBinding.hpp"
#include "ft/assert.hpp" // Tester d'autres prositions dans l'ordre d'includec

int			OCamlBinding::generate_gridG(lua_State *l)
{
	int const			top = lua_gettop(l);
	OCamlBinding *const	ocaml = OCamlBinding::instance();
	bool				solvable;
	int					w;
	Grid				gr;

	if (ocaml == nullptr)
		luaL_error(l, "genRandomGrid problem1");
	if (top > 2)
		luaL_error(l, "genRandomGrid too many parameters");
	if (top == 0)
		luaL_error(l, "genRandomGrid not enough parameters");
	if (top == 2)
	{
		if (!lua_isboolean(l, 2))
			luaL_error(l, "genRandomGrid wrong parameter");
		solvable = lua_toboolean(l, 2);
	}
	else
		solvable = true;
	w = luaL_checkinteger(l, 1);
	try
	{
		gr = ocaml->generate_grid(w, solvable);
	}
	catch (...)
	{
		luaL_error(l, "genRandomGrid problem 2");
	}
	lua_pop(l, top);
	lua_createtable(l, w * w, 0);
	for (int i = 0; i < w * w; i++)
	{
		lua_pushinteger(l, i);
		lua_pushinteger(l, gr.get(i % w, i / w));
		lua_settable(l, -3);
	}

	return (1);
}
