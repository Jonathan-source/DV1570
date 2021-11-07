#include "Application.h"
#include "Framework.h"

Application::Application()
	: device(nullptr)
	, driver(nullptr)
	, scenemgr(nullptr)
	, guienv(nullptr)
	, m_eventReceiver(EventReceiver())
	, m_sceneStateMachine(StateMachine())
{
    SetupEngine();
    SetupGameScenes();
}

void Application::Run()
{
    // Setup Lua.
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    std::thread conThread(ConsoleThread, L);
    
    u32 then = device->getTimer()->getTime();
    u32 now = device->getTimer()->getTime();

    float frameDeltaTime = static_cast<f32>(now - then) / 1000.f; // time in seconds

    while(device->run() && m_isRunning)
    {
        if (device->isWindowActive())
        {
            now = device->getTimer()->getTime();
            frameDeltaTime = static_cast<f32>(now - then) / 1000.f; //time in seconds
            
            // Update current scene.
            m_isRunning = m_sceneStateMachine.Update(m_eventReceiver, frameDeltaTime);

            then = now;

            // Render current scene.
            driver->beginScene(true, true, irr::video::SColor(255, 90, 101, 140));
            scenemgr->drawAll();
            guienv->drawAll();
            driver->endScene();
        }
        else
        {
            device->yield();
        }
    }

    device->closeDevice();								
    PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);		
    lua_close(L);										
    conThread.join();
}

void Application::SetupEngine()
{
    irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_SOFTWARE;
    params.WindowSize = irr::core::dimension2d<irr::u32>(1920, 1080);
    params.Fullscreen = false;
    params.Vsync = false;
    params.AntiAlias = 8;
    params.EventReceiver = &m_eventReceiver;
    device = irr::createDeviceEx(params);

    assert(device != nullptr && "Failed to create IrrlichtDevice.");

    device->setWindowCaption(L"Application");
    driver = device->getVideoDriver();
	scenemgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

    m_isRunning = true;
}

void Application::SetupGameScenes()
{
    m_sceneStateMachine.Add("main_menu", new MainMenu(device));
    m_sceneStateMachine.Add("game", new Game(device));
    m_sceneStateMachine.Add("highscore", new Highscore());
    m_sceneStateMachine.Add("editor", new Editor(device));

	// Set initial scene.
    m_sceneStateMachine.Change("main_menu");
}

