// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ALayout_luaCFunctions.cpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/11 17:10:07 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/13 07:57:53 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/ALayout.hpp"
#include "ftlua/ftlua.hpp"

namespace ftui
{

#define DEF_LUACFUN_GSUFFIX(NAME, NUMIN, NUMOUT)			\
int			ALayout::NAME##G(lua_State *l)					\
{															\
	return ftlua::luaCFunHelper<NUMIN, NUMOUT>(l, &ALayout::NAME);	\
}

DEF_LUACFUN_GSUFFIX(size, 1, 1)

int			ALayout::atG(lua_State *l)					
{
	return ftlua::luaCFunHelper<2, 1>(
		l, static_cast<AView*(ALayout::*)(int)>(&ALayout::at));
}

// DEF_LUACFUN_GSUFFIX(setParam, 1, 0)
// DEF_LUACFUN_GSUFFIX(addView, 1, 0)
// DEF_LUACFUN_GSUFFIX(popView, 1, 0)

};
