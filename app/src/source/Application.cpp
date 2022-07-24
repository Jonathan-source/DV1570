#include "pch.h"
#include "Application.h"
#include "ResourceManager.h"

Application::Application()
    : m_sceneStateMachine(StateMachine())
    , m_isRunning(false)
{
    L = luaL_newstate();
    luaL_openlibs(L);
}

Application::~Application()
{
    DumpStack(L);
    lua_close(L);
}

void Application::Run()
{    
    IState* currentState = nullptr;
    while (!WindowShouldClose() && m_isRunning)
    {
        currentState = m_sceneStateMachine.Current();
       
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

    RegisterLuaFunctions();

    LoadResources();

    SetupGameScenes();

    m_isRunning = true;

    return m_isRunning;
}

void Application::RegisterLuaFunctions()
{
    lua_register(L, "_IsKeyDown", wrap_IsKeyDown);
}

void Application::LoadResources()
{
    auto& recourceManager = ResourceManager::Get();
    recourceManager.SetResourcePath(Utils::Get().GetProjectPath() + "\\resources");

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
    m_sceneStateMachine.Add("Game", new Game());
    m_sceneStateMachine.Add("Highscore", new Highscore());
    m_sceneStateMachine.Add("Editor", new Editor());

	// Set initial scene
    m_sceneStateMachine.Change("MainMenu");
}

int Application::wrap_IsKeyDown(lua_State* L)
{
    if (lua_gettop(L) != 1) return -1;
    int key = (int)lua_tointeger(L, 1);
    bool isDown = IsKeyDown((KeyboardKey)key);
    lua_pushboolean(L, isDown);
    return 1;
}


