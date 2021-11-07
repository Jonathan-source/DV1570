#pragma once

#include "Player.h"
#include "StateMachine.h"

#include "MainMenu.h"
#include "Game.h"
#include "Highscore.h"
#include "Editor.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Application
{
public:
    Application();
    virtual ~Application() = default;

    void Run();

private:
    IrrlichtDevice* device;
    IVideoDriver* driver;
    ISceneManager* scenemgr;
    IGUIEnvironment* guienv;

    EventReceiver m_eventReceiver;
    StateMachine m_sceneStateMachine;
    bool m_isRunning;

    void SetupEngine();

    void SetupGameScenes();
};
