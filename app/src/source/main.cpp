#include "pch.h"
#include "Application.h"

int main(int argc, char * argv[])
{
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    std::filesystem::path pathToShow{ argc >= 2 ? argv[1] : std::filesystem::current_path() };
    std::filesystem::path projectPath;
    for (const auto& part : pathToShow) {
        projectPath /= part;
        if (part == "DV1570") break;
    }

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    Application* app = new Application(L, projectPath.string());
    
    app->Run();
    
    delete app;

    lua_close(L);

    return 0;
}