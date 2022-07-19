#pragma once

#include "Player.h"
#include "StateMachine.h"
#include "raylib.h"
#include "MainMenu.h"
#include "Game.h"
#include "Highscore.h"
#include "Editor.h"

class Application
{
public:
    Application(lua_State* L);
    virtual ~Application();

    void Run();
    
private:
    lua_State * L;
    StateMachine m_sceneStateMachine;
    bool m_isRunning;
    void SetupEngine();
    void LoadResources();
    void SetupGameScenes();
};