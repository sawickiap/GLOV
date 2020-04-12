#include <GLOV.h>

#include "Win32/PlatformWin32.h"
#include "WindowConfig.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
//int main( int argc, char *argv[] )
{
    printf("Hello world!\n");

    //GLOV::Instance* instance = nullptr;
    //GLOV::Result res = GLOV::CreateInstance(instance);
    //assert(res == GLOV::Result::Success);

    //GLOV::DestroyInstance(instance);

	PlatformWin32 app(hInstance);
	app.createConsole();
	WindowConfig hints;
	hints.width = 600;
	hints.height = 600;
	hints.title = "Test";
	//hints.windowFlags = (eWindowFlags)(eWindowFlags::Visible | eWindowFlags::FocusOnShow);
	//hints.windowFlags = ;
	app.init(hPrevInstance, pCmdLine, nCmdShow);
	app.createWindow(hints);
	app.run();
	app.terminate();
	app.deleteConsole();
	return 0;
}
