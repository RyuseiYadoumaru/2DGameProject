#include "WindowsApplication.h"

using namespace mySystem;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto winApp = new WindowsApplication;

	bool success = winApp->Setup();
	
	if (success)
	{
		winApp->Run();
	}

	winApp->Suhtdown();
	delete winApp;
	return 0;
}