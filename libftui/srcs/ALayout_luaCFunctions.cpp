// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_luaCFunctions.cpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:25 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/09 15:56:44 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/ALayout.hpp"
#include "ftui/luaCFunctions_helpers.hpp"

namespace ftui
{

#define DEF_LUACFUN_GSUFFIX(NAME, NUMIN, NUMOUT)			\
int			ALayout::NAME##G(lua_State *l)					\
{															\
	std::cout << "luaCFun : " << #NAME << std::endl;		\
	return luaCFunHelper<NUMIN, NUMOUT>(l, &ALayout::NAME);	\
}

// DEF_LUACFUN_GSUFFIX(setParam, 1, 0)
DEF_LUACFUN_GSUFFIX(size, 1, 1)
int			ALayout::atG(lua_State *l)					
{															
	return luaCFunHelper<2, 1>(
		l, static_cast<AView*(ALayout::*)(int)>(&ALayout::at));
}
// DEF_LUACFUN_GSUFFIX(at, 2, 1)
// DEF_LUACFUN_GSUFFIX(addView, 1, 0)
// DEF_LUACFUN_GSUFFIX(popView, 1, 0)

// int			AView::getIdG(lua_State *l)
// {
// 	AView *const				i = luaCFunRetreiveSelf<AView>(l, -1);
// 	std::string const *const	s = i->getId();

// 	if (s == nullptr)
// 		lua_pushnil(l);
// 	else
// 		lua_pushstring(l, s->c_str());
// 	return (1);
// }


// int			AView::getParentG(lua_State *l)
// {
// 	AView *const	i = luaCFunRetreiveSelf<AView>(l, -1);
// 	ALayout *const	p = i->getParent();

// 	if (p == nullptr)
// 		lua_pushnil(l);
// 	else
// 	{
// 		lua_pushglobaltable(l);
// 		lua_pushlightuserdata(l, p);
// 		lua_gettable(l, -2);
// 	}
// 	return (1);
// }

};
