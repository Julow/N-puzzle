// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ftlua_extend.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/11 16:30:35 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/19 17:04:31 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_EXTEND_HPP
# define FTLUA_EXTEND_HPP

#include "ftlua/ftlua.hpp"

#include "Grid.hpp"

namespace ftlua
{

template <bool USELUAERR = false>
int			push(lua_State *l, Grid const &gr)
{
	int const   w = gr.getSize();

	lua_createtable(l, w * w, 0);
	for (int i = 0; i < w * w; i++)
	{
		lua_pushinteger(l, i);
		lua_pushinteger(l, gr.get(i % w, i / w));
		lua_settable(l, -3);
	}
	return 1;
}

};

#endif // ************************************************** FTLUA_EXTEND_HPP //
