#include "Framework.h"
#include "LuaTests.h"
#include "Player.h"
#include "EventHandler.h"

#include "Game.h"
#include "Highscore.h"
#include "MainMenu.h"
#include "Editor.h"

#include "StateMachine.h"


int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Setup Lua.
	lua_State * L = luaL_newstate();
	luaL_openlibs(L);

	std::thread conThread(ConsoleThread, L);

	// Test some Lua code.
	LUA_TESTS::TEST_1(L);


	// Setup Irrlicht.
	EventHandler eventHandler;
	irr::SIrrlichtCreationParameters params;
	params.DriverType = irr::video::EDT_SOFTWARE;
	params.WindowSize = irr::core::dimension2d<irr::u32>(1920, 1080);
	params.Fullscreen = false;
	params.Vsync = false;
	params.AntiAlias = 8;
	params.EventReceiver = &eventHandler;
	irr::IrrlichtDevice* device = irr::createDeviceEx(params);
	if (!device)
		return EXIT_FAILURE;

	device->setWindowCaption(L"Application");
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();


	// Add scenes.
	StateMachine sceneStateMachine;
	{
		// Use: M, G, E, H, Q to switch between current scenes.
		sceneStateMachine.Add("main_menu", new MainMenu(device));
		sceneStateMachine.Add("game", new Game(device));
		sceneStateMachine.Add("highscore", new Highscore());
		sceneStateMachine.Add("editor", new Editor(device));
		// Set initial scene.
		sceneStateMachine.Change("main_menu");
	}

	// Main loop.
	bool isRunning = true;
	while (device->run() && isRunning)
	{
		if (device->isWindowActive())
		{
			// Update current scene.
			isRunning = sceneStateMachine.Update(eventHandler);

			// Render current scene.
			driver->beginScene(true, true, irr::video::SColor(255, 90, 101, 140));
			sceneManager->drawAll();
			guienv->drawAll();
			driver->endScene();
		}
		else
		{
			device->yield();
		}
	}
	
	// Cleanup.
	device->closeDevice();								// Close Irrlicht.
	PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);	// Close Console Window.		
	lua_close(L);										// Close Lua.
	conThread.join();									// Join Console Thread.

	return EXIT_SUCCESS;
}