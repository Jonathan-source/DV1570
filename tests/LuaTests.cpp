#include "LuaTests.h"

#include <iostream>


namespace LUA_TESTS
{

	void TEST_1()
	{
		std::cout << __FUNCTION__ << std::endl;

		luaL_dostring(g_L, "z = 10");
		lua_getglobal(g_L, "z");
		lua_Number z = (int)lua_tonumber(g_L, -1);
		std::cout << "Lua says z = " << z << std::endl;

		std::cout << "--------------------" << std::endl;
	}

	void TEST_2()
	{
		std::cout << __FUNCTION__ << std::endl;

		constexpr char* LUA_FILE = R"(
		function Return4()
			return 4
		end
		)";

		luaL_dostring(g_L, LUA_FILE);
		lua_getglobal(g_L, "Return4");

		if (lua_isfunction(g_L, -1))
		{
			lua_pcall(g_L, 0, 1, 0);
			lua_Number ret = (int)lua_tonumber(g_L, -1);
			std::cout << "Return4 = " << ret << std::endl;
		}

		std::cout << "--------------------" << std::endl;
	}

	void TEST_3()
	{
		std::cout << __FUNCTION__ << std::endl;

		const std::string filename = "test.lua";
		if (luaL_loadfile(g_L, filename.c_str()) || lua_pcall(g_L, 0, 0, 0))
		{
			std::cout << "failed to load " << filename << std::endl;
		}
		else
		{
			lua_getglobal(g_L, "x");
			lua_Number x = (int)lua_tonumber(g_L, -1); // last pushed on the stack.
			std::cout << "Lua says x = " << x << std::endl;
		}

		std::cout << "--------------------" << std::endl;
	}


} // end of namespace