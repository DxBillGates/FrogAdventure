#include"Application.h"
#include<Windows.h>
#ifdef _DEBUG
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif
	HRESULT result = CoInitializeEx(0, COINIT_MULTITHREADED);
	Application app(1280, 640, "Frog Adventure");
	if (!app.Init())return -1;
	app.Run();
	return 0;
}