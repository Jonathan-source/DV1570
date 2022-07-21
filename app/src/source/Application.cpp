#include "pch.h"
#include "Application.h"
#include "ResourceManager.h"

Application::Application(lua_State* L, const std::string& projectPath)
    : L(L)
    , m_projectPath(projectPath)
    , m_sceneStateMachine(StateMachine())
    , m_isRunning(false)
{
}

void Application::Run()
{    
    IState* currentState = nullptr;
    while (!WindowShouldClose() && m_isRunning)
    {
        currentState = m_sceneStateMachine.Current();
        
        // Update Lua?

        currentState->OnInput();

        m_isRunning = currentState->OnUpdate(GetFrameTime());

        currentState->OnRender();

        DrawFPS(10, 10);
    }

    CloseWindow();
    CloseAudioDevice();
}

bool Application::Initialize()
{
    const int screenWidth = 1280;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "The Game");

    SetTargetFPS(60);

    SetExitKey(KEY_NULL);

    InitAudioDevice();

    LoadResources();

    SetupGameScenes();

    m_isRunning = LoadGameScript();

    return m_isRunning;
}

void Application::LoadResources()
{
    auto& recourceManager = ResourceManager::Get();
    recourceManager.SetResourcePath(m_projectPath + "\\resources");

    recourceManager.GetModel("zombie.obj");
    recourceManager.GetModel("rock_1.obj");
    recourceManager.GetModel("tree_1.obj");
    recourceManager.GetModel("tree_2.obj");
    recourceManager.GetModel("cube.obj");
    recourceManager.GetModel("steve.obj");

    recourceManager.GetTexture("zombie.png");
    recourceManager.GetTexture("steve.png");
    recourceManager.GetTexture("tree_1_icon.png");
    recourceManager.GetTexture("tree_2_icon.png");
    recourceManager.GetTexture("rock_1_icon.png");
    recourceManager.GetTexture("spawner_1_icon.png");
    recourceManager.GetTexture("zombie_1_icon.png");
    recourceManager.GetTexture("startbutton.png");
    recourceManager.GetTexture("editorbutton.png");
    recourceManager.GetTexture("highscorebutton.png");
    recourceManager.GetTexture("exitbutton.png");


}

void Application::SetupGameScenes()
{
    m_sceneStateMachine.Add("MainMenu", new MainMenu());
    m_sceneStateMachine.Add("Game", new Game(L));
    m_sceneStateMachine.Add("Highscore", new Highscore());
    m_sceneStateMachine.Add("Editor", new Editor());

	// Set initial scene
    m_sceneStateMachine.Change("MainMenu");
}

bool Application::LoadGameScript()
{
    luaL_dofile(L, (m_projectPath + "/resources/scripts/demo.lua").c_str());

    if (!lua_getglobal(L, "onEvent") || !lua_isfunction(L, -1))
    {
        std::cout << "\n'onEvent' function not found\n" << std::endl;
        return false;
    }
    lua_pop(L, -1);

    if (!lua_getglobal(L, "onUpdate") || !lua_isfunction(L, -1))
    {
        std::cout << "\n'onUpdate' function not found\n" << std::endl;
        return false;
    }
    lua_pop(L, -1);

    if (!lua_getglobal(L, "onRender") || !lua_isfunction(L, -1))
    {
        std::cout << "\n'onRender' function not found\n" << std::endl;
        return false;
    }
    lua_pop(L, -1);

    if (!lua_getglobal(L, "onInit") || !lua_isfunction(L, -1))
    {
        std::cout << "\n'onInit' function not found\n" << std::endl;
        return false;
    }

    // Call 'onInit' function.
    return CheckLua(L, lua_pcall(L, 0, 0, 0));
}
