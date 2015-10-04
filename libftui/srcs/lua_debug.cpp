// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   lua_debug.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 15:25:06 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/04 16:04:08 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/libftui.hpp"

#include <vector>
#include <iostream>//de

extern "C"
{
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}

#include "ftui/Activity.hpp"

static std::vector<std::string> const		funs{{
		"\
ftpt = function(t)														\
	print(tostring(t)..' #'..tostring(#t)..' mt:'..tostring(getmetatable(t))); \
	print('pairs:');													\
	for k,v in pairs(t) do												\
		print(string.format('%20s(%3.3s): (%3.3s){%s}'					\
			, tostring(k), type(k), type(v), tostring(v)))				\
	end;																\
	print('ipairs:');													\
	for k,v in ipairs(t) do												\
		print(string.format('%20s(%3.3s): (%3.3s){%s}'					\
			, tostring(k), type(k), type(v), tostring(v)))				\
	end;																\
end;																	\
"
		}};

namespace ftui
{

void		lua_pushUtils(Activity const &a)
{
	lua_State	*l = a.getLuaState();

	for (auto it : funs)
	{
		if (luaL_dostring(l, it.c_str()) == 0)
			; //TODO throw
	}
	return ;
}

};
