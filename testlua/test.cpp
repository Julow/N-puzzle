// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   test.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/24 07:31:01 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/05 14:04:52 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <functional>
#include <cmath>
#include <stdexcept>

#include "ftui/lua.hpp"

/*
envdump
for k,v in pairs(_G) do print(string.format("%20s: (%3.3s){%s}", tostring(k), type(v), tostring(v))) end
for k,v in ipairs(_G) do print(string.format("%20s: (%3.3s){%s}", tostring(k), type(v), tostring(v))) end

for k,v in pairs(t) do print(string.format("%20s: (%3.3s){%s}", tostring(k), type(v), tostring(v))) end
for k,v in ipairs(t) do print(string.format("%20s: (%3.3s){%s}", tostring(k), type(v), tostring(v))) end

function pt(t) print(tostring(t).." #"..tostring(#t).." mt:"..tostring(getmetatable(t))); for k,v in pairs(t) do print(string.format("%20s(%3.3s): (%3.3s){%s}", tostring(k), type(k), type(v), tostring(v))) end; print(""); for k,v in ipairs(t) do print(string.format("%20s(%3.3s): (%3.3s){%s}", tostring(k), type(k), type(v), tostring(v))) end end

base = {fun1 = function (self) print(tostring(self).." fun1") end}; base.__index = base;
deriv = {}; setmetatable(deriv, base); deriv.__index = deriv


*/
namespace ftui
{
void		luaFT_stackdump(lua_State *L)
{
	int const				top = lua_gettop(L);
	int						i;
	std::function<void()>	funcs[] =
	{
		[=, &i](){std::cout << "  none" << "\n";},
		[=, &i](){std::cout << "   nil" << "\n";},
		[=, &i](){std::cout << "  bool: " << lua_toboolean(L, i) << "\n";},
		[=, &i](){std::cout << " lusrd" << "\n";},
		[=, &i](){std::cout << "   nbr: " << lua_tonumber(L, i) <<  "\n";},
		[=, &i](){std::cout << "   str: " << lua_tostring(L, i) << "\n";},
		[=, &i](){std::cout << "   tab" << "\n";},
		[=, &i](){std::cout << "  func: " << (void*)lua_tocfunction(L, i) << "\n";},
		[=, &i](){std::cout << "  usrd" << "\n";},
		[=, &i](){std::cout << "thread" << "\n";},
	};
	std::cout << "Stack dump: " << top << " Elements" << std::endl;	
	for (i = 1; i <= top; i++)
	{
		std::cout << "[" << i << "]";
		funcs[lua_type(L, i) + 1]();
	}
	return ;
}
}

static	int l_sin (lua_State *L)
{
	std::cout << "\nMYSIN BEGIN" << std::endl;
	ftui::luaFT_stackdump(L);
	double const	d = luaL_checknumber(L, -1);
	// double const	d = lua_tonumber(L, 1);
	ftui::luaFT_stackdump(L);
	std::cout << "l_sin got: " << d << std::endl;
	lua_pushnumber(L, sin(d));
	ftui::luaFT_stackdump(L);
	// throw (std::exception());
	std::cout << "MYSIN END\n" << std::endl;
	return 1;
}

int main (void)
{
	int			error;
	lua_State	*L = luaL_newstate();
	std::string	buf;

	luaL_openlibs(L);
	lua_pushcfunction(L, l_sin);
	ftui::luaFT_stackdump(L);
	lua_setglobal(L, "mysin");
	ftui::luaFT_stackdump(L);
	lua_pushnil(L);
	lua_pushboolean(L, 42);
	lua_pushboolean(L, 1);
	lua_pushstring(L, "hello");
	lua_pushnumber(L, 42.);
	ftui::luaFT_stackdump(L);

	while (!std::cin.eof())
	{
		std::getline(std::cin, buf);
		try
		{
		error = luaL_loadbuffer(L, buf.c_str(), buf.length(), "line") ||
			lua_pcall(L, 0, 0, 0);
		}
		catch (std::exception &e)
		{
			std::cout << "BEGIN OF CATCH" << std::endl;
			ftui::luaFT_stackdump(L);
			std::cout << "END OF CATCH" << std::endl;
			
		}
		
		if (error)
		{
			std::cout << "lol ERROR(" << error << "): " << lua_tostring(L, -1) << std::endl;
			lua_pop(L, 1); 
		}
		// ftui::luaFT_stackdump(L);
	}

	std::cout << "LUA_ERRERR" << " " <<LUA_ERRERR<< "\n";
	std::cout << "LUA_ERRFILE" << " " <<LUA_ERRFILE<< "\n";
	std::cout << "LUA_ERRGCMM" << " " <<LUA_ERRGCMM<< "\n";
	std::cout << "LUA_ERRMEM" << " " <<LUA_ERRMEM<< "\n";
	std::cout << "LUA_ERRRUN" << " " <<LUA_ERRRUN<< "\n";
	std::cout << "LUA_ERRSYNTAX" << " " <<LUA_ERRSYNTAX<< "\n";
	std::cout << "LUA_HOOKCALL" << " " <<LUA_HOOKCALL<< "\n";
	std::cout << "LUA_HOOKCOUNT" << " " <<LUA_HOOKCOUNT<< "\n";
	std::cout << "LUA_HOOKLINE" << " " <<LUA_HOOKLINE<< "\n";
	std::cout << "LUA_HOOKRET" << " " <<LUA_HOOKRET<< "\n";
	std::cout << "LUA_HOOKTAILCALL" << " " <<LUA_HOOKTAILCALL<< "\n";
	std::cout << "LUA_MASKCALL" << " " <<LUA_MASKCALL<< "\n";
	std::cout << "LUA_MASKCOUNT" << " " <<LUA_MASKCOUNT<< "\n";
	std::cout << "LUA_MASKLINE" << " " <<LUA_MASKLINE<< "\n";
	std::cout << "LUA_MASKRET" << " " <<LUA_MASKRET<< "\n";
	std::cout << "LUA_MAXINTEGER" << " " <<LUA_MAXINTEGER<< "\n";
	std::cout << "LUA_MININTEGER" << " " <<LUA_MININTEGER<< "\n";
	std::cout << "LUA_MINSTACK" << " " <<LUA_MINSTACK<< "\n";
	std::cout << "LUA_MULTRET" << " " <<LUA_MULTRET<< "\n";
	std::cout << "LUA_NOREF" << " " <<LUA_NOREF<< "\n";
	std::cout << "LUA_OK" << " " <<LUA_OK<< "\n";
	std::cout << "LUA_OPADD" << " " <<LUA_OPADD<< "\n";
	std::cout << "LUA_OPBAND" << " " <<LUA_OPBAND<< "\n";
	std::cout << "LUA_OPBNOT" << " " <<LUA_OPBNOT<< "\n";
	std::cout << "LUA_OPBOR" << " " <<LUA_OPBOR<< "\n";
	std::cout << "LUA_OPBXOR" << " " <<LUA_OPBXOR<< "\n";
	std::cout << "LUA_OPDIV" << " " <<LUA_OPDIV<< "\n";
	std::cout << "LUA_OPEQ" << " " <<LUA_OPEQ<< "\n";
	std::cout << "LUA_OPIDIV" << " " <<LUA_OPIDIV<< "\n";
	std::cout << "LUA_OPLE" << " " <<LUA_OPLE<< "\n";
	std::cout << "LUA_OPLT" << " " <<LUA_OPLT<< "\n";
	std::cout << "LUA_OPMOD" << " " <<LUA_OPMOD<< "\n";
	std::cout << "LUA_OPMUL" << " " <<LUA_OPMUL<< "\n";
	std::cout << "LUA_OPPOW" << " " <<LUA_OPPOW<< "\n";
	std::cout << "LUA_OPSHL" << " " <<LUA_OPSHL<< "\n";
	std::cout << "LUA_OPSHR" << " " <<LUA_OPSHR<< "\n";
	std::cout << "LUA_OPSUB" << " " <<LUA_OPSUB<< "\n";
	std::cout << "LUA_OPUNM" << " " <<LUA_OPUNM<< "\n";
	
	std::cout << "LUA_REFNIL" << " " <<LUA_REFNIL<< "\n";
	std::cout << "LUA_REGISTRYINDEX" << " " <<LUA_REGISTRYINDEX<< "\n";
	std::cout << "LUA_RIDX_GLOBALS" << " " <<LUA_RIDX_GLOBALS<< "\n";
	std::cout << "LUA_RIDX_MAINTHREAD" << " " <<LUA_RIDX_MAINTHREAD<< "\n";
	
	std::cout << "LUA_TBOOLEAN" << " " <<LUA_TBOOLEAN<< "\n";
	std::cout << "LUA_TFUNCTION" << " " <<LUA_TFUNCTION<< "\n";
	std::cout << "LUA_TLIGHTUSERDATA" << " " <<LUA_TLIGHTUSERDATA<< "\n";
	std::cout << "LUA_TNIL" << " " <<LUA_TNIL<< "\n";
	std::cout << "LUA_TNONE" << " " <<LUA_TNONE<< "\n";
	std::cout << "LUA_TNUMBER" << " " <<LUA_TNUMBER<< "\n";
	std::cout << "LUA_TSTRING" << " " <<LUA_TSTRING<< "\n";
	std::cout << "LUA_TTABLE" << " " <<LUA_TTABLE<< "\n";
	std::cout << "LUA_TTHREAD" << " " <<LUA_TTHREAD<< "\n";
	std::cout << "LUA_TUSERDATA" << " " <<LUA_TUSERDATA<< "\n";

//	std::cout << "LUA_USE_APICHECK" << " " <<LUA_USE_APICHECK<< "\n";
	std::cout << "LUA_YIELD" << " " <<LUA_YIELD<< "\n";
	std::cout << "LUAL_BUFFERSIZE" << " " <<LUAL_BUFFERSIZE<< "\n";
	
	lua_close(L);
	std::cout << "done" << std::endl;
	return 0;
}
