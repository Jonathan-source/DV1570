#pragma once

// Standard library.
#include <iostream>
#include <thread>
#include <cassert>
#include <chrono>

// Lua.
#include "lua.hpp"

#ifdef _WIN32
	#include <Windows.h>
	#pragma comment(lib, "../libs/lua542/liblua54.a")

	void ConsoleThread(lua_State* L)
	{
		char command[1000];
		while (GetConsoleWindow())
		{
			memset(command, 0, 1000);
			std::cin.getline(command, 1000);
			if (luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0))
				std::cout << lua_tostring(L, -1) << '\n';
		}
	}
#endif


// Irrlicht.
#include <irrlicht.h>
#pragma comment(lib, "../libs/irrlicht/lib/x64/Irrlicht.lib")