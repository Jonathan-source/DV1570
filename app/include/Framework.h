#pragma once

// Standard library.
#include <iostream>
#include <thread>


// Lua.
#include "lua.hpp"

#ifdef _WIN32
	#include <Windows.h>
	#pragma comment(lib, "../libs/lua542/liblua54.a")
#endif


// Irrlicht.
#include <irrlicht.h>
#pragma comment(lib, "../libs/irrlicht/lib/x64/Irrlicht.lib")