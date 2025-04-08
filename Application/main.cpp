#include <iostream>
#include <thread>
#include "lua.hpp"
#include <string>
#include <Windows.h>

void DumpError(lua_State* L)
{
	if (lua_gettop(L) && lua_isstring(L, -1))
	{
		std::cout << "Lua error: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
}

void ConsoleThreadFunction(lua_State* L)
{
	std::string input;
	while (GetConsoleWindow()) 
	{
		std::cout << "> ";
		std::getline(std::cin, input);

		if (luaL_dostring(L, input.c_str()) != LUA_OK);
		{
			DumpError(L);
		}
	}
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	std::thread consolethread(ConsoleThreadFunction, L);

	bool running = true;
	while (running)
	{
		//Update 
		//render

		//std::cout << "Toe says hello" << std::endl;
	}


	std::cout << "Hello World!" << std::endl;
	return 0;
}