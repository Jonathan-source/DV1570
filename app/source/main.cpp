#include "Framework.h"
#include "EventHandler.h"

#include "Game.h"
#include "Highscore.h"
#include "MainMenu.h"
#include "Editor.h"

#include "StateMachine.h"


void TEST_LUA(lua_State* L)
{
	// Test 1.
	{
		luaL_dostring(L, "z = 10");
		lua_getglobal(L, "z");
		lua_Number z = (int)lua_tonumber(L, -1);
		std::cout << "Lua says z = " << z << std::endl;
	}

	// Test 2.
	{
		constexpr char* LUA_FILE = R"(
		function Return4()
			return 4
		end
		)";

		luaL_dostring(L, LUA_FILE);
		lua_getglobal(L, "Return4");

		if (lua_isfunction(L, -1))
		{
			lua_pcall(L, 0, 1, 0);
			lua_Number ret = (int)lua_tonumber(L, -1);
			std::cout << "Return4 = " << ret << std::endl;
		}
	}

	// Test 3.
	{
		// Todo: Load scripts and its functions & variables.
		const std::string filename = "test.lua";
		if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0))
		{
			std::cout << "failed to load " << filename << std::endl;
		}
		else
		{
			lua_getglobal(L, "x");
			lua_Number x = (int)lua_tonumber(L, -1); // last pushed on the stack.
			std::cout << "Lua says x = " << x << std::endl;
		}
	}
}



int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Setup Lua.
	lua_State * L = luaL_newstate();
	luaL_openlibs(L);
	std::thread conThread(ConsoleThread, L);

	TEST_LUA(L);

	// Setup Irrlicht.
	EventHandler eventHandler;
	irr::SIrrlichtCreationParameters params;
	params.DriverType = irr::video::EDT_SOFTWARE;
	params.WindowSize = irr::core::dimension2d<irr::u32>(800, 600);
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
	sceneStateMachine.Add("main_menu", new MainMenu());
	sceneStateMachine.Add("game", new Game());
	sceneStateMachine.Add("highscore", new Highscore());
	sceneStateMachine.Add("editor", new Editor());

	// Set initial scene.
	sceneStateMachine.Change("main_menu");

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
	(void)device->drop();
	conThread.join();
	lua_close(L);

	//PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
	return EXIT_SUCCESS;
}