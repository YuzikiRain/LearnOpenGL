#include <BorderlessEngine.h>

int main()
{
	BorderlessEngine::InitializeWindow();
	BorderlessEngine::InitSystems();
	BorderlessEngine::UpdateSystems();
	BorderlessEngine::Quit();
}

