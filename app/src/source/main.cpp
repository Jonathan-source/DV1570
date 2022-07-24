#include "pch.h"
#include "Application.h"

int main(int argc, char * argv[])
{
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    std::filesystem::path pathToShow{ std::filesystem::current_path() };
    std::filesystem::path projectPath;
    for (const auto& part : pathToShow) {
        projectPath /= part;
        if (part == "DV1570") break;
    }
    Utils::Get().SetProjectPath(projectPath.string());

    Application* app = new Application();

    if (app->Initialize()) {
        app->Run();
    }
   
    delete app;

    return 0;
}