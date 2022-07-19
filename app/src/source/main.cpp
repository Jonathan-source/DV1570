#include "pch.h"
#include "Application.h"

int main()
{
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    Application* app = new Application(L);
    app->Run();
    delete app;

    lua_close(L);

    return 0;
}