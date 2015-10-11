// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   lua_debug.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 15:25:06 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/11 17:58:56 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/libftui.hpp"

#include <vector>
#include <iostream>//de

#include "ftui/Activity.hpp"
#include "lua.hpp"

#define TOSTRING(...) #__VA_ARGS__

static std::vector<std::string> const		funs{ //TODO omg lol mdr
{"															\
ft_tostring = function(v)									\
	if type(v) == 'function' then							\
		return string.gsub(tostring(v), 'function: ', 'FN');\
	elseif type(v) == 'table' then							\
		return string.gsub(tostring(v), 'table: ', 'TA');	\
	elseif type(v) == 'userdata' then						\
		return string.gsub(tostring(v), 'userdata: ', 'UD');\
	end														\
	return tostring(v);										\
end															\
"},
{"\
ft_ptab = function(t, p1, p2, p3, p4)										\n \
	local maxDepth = p1 or -1;												\n \
	local curDepth = p2 or 0;												\n \
	local excludedK = p3 or {[os] = true, [package] = true					\n \
		, [math] = true, [string] = true, [debug] = true					\n \
		, [io] = true, [bit32] = true, [table] = true						\n \
		, [coroutine] = true, [utf8] = true};								\n \
	local curTab = p4 or '';												\n \
	local header = string.format('%1.1d*%s', curDepth, curTab);				\n \
	local curCol = '\033[4'..tostring(1 + (curDepth) % 5)..'m'				\n \
	local nextTab = curTab..curCol..'**'..'\033[0m';						\n \
	local empty = true														\n \
																			\n \
	excludedK[t] = true;													\n \
	if curDepth == 0 then													\n \
		print(string.format('******%s (#%d) metatab:%s ***************'		\n \
			, tostring(t), tostring(#t), tostring(getmetatable(t)))); 		\n \
	end																		\n \
	for k,v in pairs(t) do													\n \
		local expand = maxDepth ~= curDepth and type(v) == 'table'			\n \
			and excludedK[v] == nil;										\n \
		local mt = '';														\n \
		local lcol = '';													\n \
		local rcol = '';													\n \
		local kstr = string.sub(ft_tostring(k), -30 + 2 * curDepth);		\n \
																			\n \
		empty = false														\n \
		if type(v) == 'table' then											\n \
			mt = string.format(' mt{%s}', ft_tostring(getmetatable(v)))		\n \
		end																	\n \
		if expand then														\n \
			lcol = curCol													\n \
			rcol = '\033[0m'												\n \
		end																	\n \
		kstr = string.format('[%s]', kstr);									\n \
		kstr = string.format('%32s', kstr);									\n \
		kstr = string.sub(kstr, -32 + 2 * curDepth);						\n \
		print(string.format('%s%s%s%3.3s/%3.3s{%s}%s%s'						\n \
		, header, lcol, kstr, type(k), type(v), ft_tostring(v), rcol, mt));	\n \
		if expand then														\n \
			mt = ft_ptab(v, maxDepth, curDepth + 1, excludedK, nextTab);	\n \
		end																	\n \
	end;																	\n \
	if empty then															\n \
		print(string.format('%s', header));									\n \
	end																		\n \
end;																		\n \
"},
{TOSTRING(
ft_pchildren = function(t, tab)
	tab = tab or '**';

	if t == nil or t[0] == nil or type(t[0]) ~= 'userdata' then
		print('wrong ft_pchildren Argument:', t);
		return ;
	end
	n = t.size and t:size() or 0;
	print(string.format('%s %s(%s) %dchildren'
		, tab, ft_tostring(t:getId()), ft_tostring(t), n));
	tab = tab..'**';
	for i=0,n - 1 do
		ft_pchildren(t:at(i), tab);
	end
end;
)}
};

namespace ftui
{

void		lua_pushUtils(Activity const &a)	// TODO accept luaState, move ftlua
{
	lua_State	*l = a.getLuaState();

	for (auto const &it : funs)
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
