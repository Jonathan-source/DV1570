#include "Application.h"

Application::Application():
    m_sceneStateMachine(StateMachine())
{
    SetupEngine();
    SetupGameScenes();
}

void Application::Run()
{
    // Setup Lua.
    //lua_State* L = luaL_newstate();
    //luaL_openlibs(L);
    //std::thread conThread(ConsoleThread, L);

    float frameDeltaTime = GetFrameTime(); // time in seconds
        // Main game loop
    while (!WindowShouldClose())    // Detect window close t_startButton or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        frameDeltaTime = GetFrameTime();
        m_isRunning = m_sceneStateMachine.Update(frameDeltaTime);
        //----------------------------------------------------------------------------------
    }

}

void Application::SetupEngine()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    InitAudioDevice();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
}

void Application::SetupGameScenes()
{
    m_sceneStateMachine.Add("main_menu", new MainMenu());
    m_sceneStateMachine.Add("game", new Game());
    m_sceneStateMachine.Add("highscore", new Highscore());
    m_sceneStateMachine.Add("editor", new Editor());

	//Set initial scene.
    m_sceneStateMachine.Change("main_menu");
}