
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
			std::cout << "lol ERROR:" << lua_tostring(L, -1) << std::endl;
			lua_pop(L, 1); 
		}
	}
	
	lua_close(L);
	std::cout << "done" << std::endl;
	return 0;
}
