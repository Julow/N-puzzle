// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   push_utils.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/13 07:41:25 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/12 14:11:11 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <vector>

#include "ftlua/ftlua.hpp"
#include "ft/assert.hpp"

#define TOSTRING(...) #__VA_ARGS__

static std::vector<std::string> const		funs{ //TODO omg lol mdr
{"ft = {};"},
{"															\
ft.tostring = function(v)									\
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
ft.ptab = function(t, p1, p2, p3, p4)										\n \
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
		local kstr = string.sub(ft.tostring(k), -30 + 2 * curDepth);		\n \
																			\n \
		empty = false														\n \
		if type(v) == 'table' then											\n \
			mt = string.format(' mt{%s}', ft.tostring(getmetatable(v)))		\n \
		end																	\n \
		if expand then														\n \
			lcol = curCol													\n \
			rcol = '\033[0m'												\n \
		end																	\n \
		kstr = string.format('[%s]', kstr);									\n \
		kstr = string.format('%32s', kstr);									\n \
		kstr = string.sub(kstr, -32 + 2 * curDepth);						\n \
		print(string.format('%s%s%s%3.3s/%3.3s{%s}%s%s'						\n \
		, header, lcol, kstr, type(k), type(v), ft.tostring(v), rcol, mt));	\n \
		if expand then														\n \
			mt = ft.ptab(v, maxDepth, curDepth + 1, excludedK, nextTab);	\n \
		end																	\n \
	end;																	\n \
	if empty then															\n \
		print(string.format('%s', header));									\n \
	end																		\n \
end;																		\n \
"},
{"\
ft.pchildren = function(t, tab)										\
	tab = tab or '**';												\
																	\
	if t == nil or t[0] == nil or type(t[0]) ~= 'userdata' then		\
		print('wrong ft.pchildren Argument:', t);					\
		return ;													\
	end																\
	n = t.size and t:size() or 0;									\
	print(string.format('%s %s(%s) %dchildren'						\
		, tab, ft.tostring(t:getId()), ft.tostring(t), n));			\
	tab = tab..'**';												\
	for _, v in ipairs(t) do										\
		ft.pchildren(v, tab);										\
	end																\
end;																\
		"},
{"\
ft.pparents = function(t)											\
	if t == nil or t[0] == nil or type(t[0]) ~= 'userdata' then		\
		print('wrong ft.pparents Argument:', t);					\
		return ;													\
	end																\
	p = t:getParent()												\
	n = t.size and t:size() or 0;									\
	if p == nil then												\
		print(string.format('** %s(%s) %dchildren'					\
			, ft.tostring(t:getId()), ft.tostring(t), n));			\
		return 2;													\
	else															\
		i = ft.pparents(p);											\
		tab = string.rep('**', i);									\
		print(string.format('%s %s(%s) %dchildren'					\
			,tab , ft.tostring(t:getId()), ft.tostring(t), n));		\
		return i + 1;												\
	end																\
end;																\
		"},
{"\
ft.finalize_template = function(t, p)						\
        t.__index = t;                                      \
        if p ~= nil then                                    \
            setmetatable(t, p);                             \
            if t.__ipairs == nil then                       \
                t.__ipairs = p.__ipairs                     \
            end                                             \
        end                                                 \
    end"},
{"\
ft.push_view = function(metatab, ud, id)		\
	local t = {};								\
												\
	setmetatable(t, metatab);					\
	t.__index = t;								\
	t[0] = ud;									\
	if id ~= nil then							\
		_G[id] = t;								\
	end											\
	_G[ud] = t;									\
end"},
};

namespace ftlua
{

void		pushUtils(lua_State *l)
{
	int		err;

	for (auto const &it : funs)
	{
		err = luaL_dostring(l, it.c_str());
		FTASSERT(err == LUA_OK);			
	}
	return ;
}

};
