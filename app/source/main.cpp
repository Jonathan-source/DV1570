#include "Application.h"

int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	const auto app = new Application();
	app->Run();
	delete app;

	return EXIT_SUCCESS;
}