// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ALayout_luaHandler.cpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/11 17:10:07 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/21 08:47:37 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/ALayout.hpp"

namespace ftui
{

#define DEF_LUACFUN_GSUFFIX(NAME, NUMIN, NUMOUT)			\
int			ALayout::NAME##G(lua_State *l)					\
{															\
	return ftlua::handle<NUMIN, NUMOUT>(l, &ALayout::NAME);	\
}

DEF_LUACFUN_GSUFFIX(size, 1, 1)

int			ALayout::atG(lua_State *l)
{
	return ftlua::handle<2, 1>(
		l, static_cast<AView*(ALayout::*)(int)>(&ALayout::at));
}

int			ALayout::addViewG(lua_State *l)
{
	ALayout			*self = ftlua::retrieveSelf<ALayout>(l, 1);
	AView			*v = ftlua::retrieveSelf<AView>(l, 1);

	if (lua_gettop(l) != 0)
		luaL_error(l, "Too many arguments");
	self->addView(v);
	return 0;
}

// DEF_LUACFUN_GSUFFIX(setParam, 1, 0)
// DEF_LUACFUN_GSUFFIX(addView, 2, 0)
// DEF_LUACFUN_GSUFFIX(popView, 1, 0)

};
