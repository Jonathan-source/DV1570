#include "Application.h"

Application::Application():
    m_sceneStateMachine(StateMachine())
{
    SetupEngine();
    SetupGameScenes();
}

void Application::Run()
{    
    IState* currentState = nullptr;
    while (!WindowShouldClose())
    {
        currentState = m_sceneStateMachine.Current();
        
        currentState->OnInput();

        currentState->OnUpdate(GetFrameTime());

        currentState->OnRender();

        DrawFPS(10, 10);
    }
}

void Application::SetupEngine()
{
    const int screenWidth = 1280;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    InitAudioDevice();

    SetTargetFPS(60);
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