#pragma once

// Include Lua, assumes it is local to this file
extern "C"
{
#include "../libs/lua542/include/lua.h"
#include "../libs/lua542/include/lauxlib.h"
#include "../libs/lua542/include/lualib.h"
}

// Link to lua library
#ifdef _WIN32
#pragma comment(lib, "../libs/lua542/liblua54.a")
#endif

// RayLib
#include <raylib.h>
#include <raymath.h>

// Standard
#include <string>
#include <string_view>
#include <exception>
#include <filesystem>
#include <chrono>
#include <iostream>
#include <sstream>
#include <fstream>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <memory>
#include <cassert> 
#include <unordered_map>
#include <vector>
#include <array>
#include <iterator>
#include <set>
#include <queue>
#include <condition_variable>
#include <bitset>
#include <algorithm>
#include <cmath>
#include <functional>
#include <math.h>
