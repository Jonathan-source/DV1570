#pragma once
#include <iostream>
#include <lauxlib.h>


void LUA_TESTS(lua_State* L)
{
	// Test 1.
	{
		luaL_dostring(L, "z = 10");
		lua_getglobal(L, "z");
		lua_Number z = (int)lua_tonumber(L, -1);
		std::cout << "Lua says z = " << z << std::endl;
	}

	// Test 2.
	{
		constexpr char* LUA_FILE = R"(
		function Return4()
			return 4
		end
		)";

		luaL_dostring(L, LUA_FILE);
		lua_getglobal(L, "Return4");

		if (lua_isfunction(L, -1))
		{
			lua_pcall(L, 0, 1, 0);
			lua_Number ret = (int)lua_tonumber(L, -1);
			std::cout << "Return4 = " << ret << std::endl;
		}
	}

	// Test 3.
	{
		// Todo: Load scripts and its functions & variables.
		const std::string filename = "test.lua";
		if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0))
		{
			std::cout << "failed to load " << filename << std::endl;
		}
		else
		{
			lua_getglobal(L, "x");
			lua_Number x = (int)lua_tonumber(L, -1); // last pushed on the stack.
			std::cout << "Lua says x = " << x << std::endl;
		}
	}
}
