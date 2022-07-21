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
    Application(lua_State* L, const std::string &projectPath);
    virtual ~Application() = default;

    void Run();
    
private:
    lua_State * L;
    std::string m_projectPath;
    StateMachine m_sceneStateMachine;
    bool m_isRunning;

    void SetupEngine();
    void LoadResources();
    void SetupGameScenes();
};