#include "Framework.h"

#ifdef _WIN32
	void ConsoleThread(lua_State* L)
	{
		char command[1000];
		while (GetConsoleWindow()) 
		{
			memset(command, 0, 1000);
			std::cin.getline(command, 1000);
			if (luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0))
				std::cout << lua_tostring(L, -1) << '\n';
		}
	}
#endif



int main()
{
	// Setup Lua.
	lua_State * L = luaL_newstate();
	luaL_openlibs(L);
	std::thread conThread(ConsoleThread, L);

	// Test Lua.
	luaL_dostring(L, "z = 10");
	lua_getglobal(L, "z");
	lua_Number z = (int)lua_tonumber(L, -1);
	std::cout << "Lua says z = " << z << std::endl;

	// Todo: Load scripts and its functions & variables.
	const std::string filename = "test.lua";
	if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0))
	{
		std::cout << "failed to load " << filename << std::endl;
	}
	else
	{
		lua_getglobal(L, "x");
		lua_Number x = (int)lua_tonumber(L, -1);
		std::cout << "Lua says x = " << x << std::endl;
	}




	// Setup Irrlicht. 
	irr::SIrrlichtCreationParameters params;
	params.DriverType = irr::video::EDT_SOFTWARE;
	params.WindowSize = irr::core::dimension2d<irr::u32>(800, 600);
	params.Fullscreen = false;
	params.Vsync = false;
	params.AntiAlias = 8;
	irr::IrrlichtDevice* device = irr::createDeviceEx(params);
	if (!device)
		return EXIT_FAILURE;

	device->setWindowCaption(L"Application");
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	// Main loop.
	while (device->run())
	{
		if (device->isWindowActive())
		{
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

	return EXIT_SUCCESS;
}