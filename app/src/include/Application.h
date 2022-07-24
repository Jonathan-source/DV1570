#pragma once

#include "Player.h"
#include "StateMachine.h"
#include "raylib.h"
#include "MainMenu.h"
#include "Game.h"
#include "Highscore.h"
#include "Editor.h"
#include "Utility.h"

class Application
{
public:
    Application();
    virtual ~Application();

    bool Initialize();

    void Run();
    
private:
    lua_State* L;
    StateMachine m_sceneStateMachine;
    bool m_isRunning;

    void RegisterLuaFunctions();
    void LoadResources();
    void SetupGameScenes();

    // LuaFunctions

    // LuaWrappers
    static int wrap_IsKeyDown(lua_State * L);
};