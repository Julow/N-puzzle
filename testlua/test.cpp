
#include <iostream>
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
	
int main (void)
{
	std::cout << "hello world" << std::endl;
	int			error;
	lua_State	*L = luaL_newstate();
	std::string	buf;

	luaL_openlibs(L);
	while (!std::cin.eof())
	{
		std::getline(std::cin, buf);
		error = luaL_loadbuffer(L, buf.c_str(), buf.length(), "line") ||
			lua_pcall(L, 0, 0, 0);
		if (error)
		{
			std::cout << "lol ERROR(" << error << "): " << lua_tostring(L, -1) << std::endl;
			lua_pop(L, 1); 
		}
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
