// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   lua_debug.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 15:25:06 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/09 13:54:10 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/libftui.hpp"

#include <vector>
#include <iostream>//de

#include "ftui/Activity.hpp"
#include "ftui/lua.hpp"

static std::vector<std::string> const		funs{{ //TODO omg lol mdr
		"\
ftpt = function(t, p1, p2, p3)												\n \
	local maxDepth = p1 or -1;												\n \
	local curDepth = p2 or 0;												\n \
	local excludedK = p3 or {[package] = true, [os] = true					\n \
		, [math] = true, [string] = true, [debug] = true					\n \
		, [io] = true, [bit32] = true, [table] = true						\n \
		, [coroutine] = true, [utf8] = true};								\n \
	local tab = string.format('%1.1d*%s'									\n \
		, curDepth, string.rep('**', curDepth));							\n \
																			\n \
	excludedK[t] = true;													\n \
	if curDepth == 0 then													\n \
		print(string.format('******%s (#%d) metatab:%s ***************'		\n \
			, tostring(t), tostring(#t), tostring(getmetatable(t)))); 		\n \
	end																		\n \
	for k,v in pairs(t) do													\n \
		local mt = '';														\n \
		if type(v) == 'table' then											\n \
			mt = string.format(' mt{%s}', tostring(getmetatable(v)))		\n \
		end																	\n \
		local kstr = string.format('%30s', tostring(k));					\n \
		kstr = string.sub(kstr, -30 + 2 * curDepth);						\n \
		print(string.format('%s[%s]%3.3s/%3.3s{%s}%s'						\n \
			, tab, kstr, type(k), type(v), tostring(v), mt));				\n \
		if maxDepth ~= curDepth												\n \
			and type(v) == 'table'											\n \
			and excludedK[v] == nil then									\n \
			mt = ftpt(v, maxDepth, curDepth + 1, excludedK);				\n \
		end																	\n \
	end;																	\n \
end;																		\n \
"
			}};
//			then string.format(' metatab:%s', tostring(getmetatable(t)))\n	
namespace ftui
{

void		lua_pushUtils(Activity const &a)
{
	lua_State	*l = a.getLuaState();

	for (auto it : funs)
	{
		if (luaL_dostring(l, it.c_str()))
		{
			std::cout << luaL_checkstring(l, -1) << std::endl;
			throw std::exception(); //TODO throw
		}
	}
	return ;
}

};
