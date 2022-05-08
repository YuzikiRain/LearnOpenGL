#include <BorderlessEngine.h>

int main()
{
	BorderlessEngine::InitializeWindow();
	BorderlessEngine::InitSystems();
	BorderlessEngine::GameLoop();
	BorderlessEngine::Quit();
}

