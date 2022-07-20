#include "pch.h"
#include "Application.h"
#include "ResourceManager.h"

Application::Application(lua_State* L)
    : L(L)
    , m_sceneStateMachine(StateMachine())
{
    SetupEngine();
    LoadResources();
    SetupGameScenes();
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

void Application::SetupEngine()
{
    const int screenWidth = 1280;
    const int screenHeight = 800;
    m_isRunning = true;

    InitWindow(screenWidth, screenHeight, "The Game");
    SetExitKey(KEY_NULL);

    InitAudioDevice();

    SetTargetFPS(60);
}

void Application::LoadResources()
{
    auto& recourceManager = ResourceManager::Get();
    recourceManager.SetResourcePath("../resources");

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