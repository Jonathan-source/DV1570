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
    Application();
    virtual ~Application() = default;

    void Run();

private:
    StateMachine m_sceneStateMachine;
    bool m_isRunning;

    void SetupEngine();

    void SetupGameScenes();
};