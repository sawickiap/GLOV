#include "pch.h"
#include "../include/GLOV.h"

#include "ApplicationWin32.h"
#include "WindowConfig.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
//int main( int argc, char *argv[] )
{
    printf("Hello world!\n");

    //GLOV::Instance* instance = nullptr;
    //GLOV::Result res = GLOV::CreateInstance(instance);
    //assert(res == GLOV::Result::Success);

    //GLOV::DestroyInstance(instance);

	ApplicationWin32 app(hInstance);
	WindowConfig hints;
	hints.width = 600;
	hints.height = 600;
	hints.title = "Test";
	hints.windowFlags = eWindowFlags::Default;
	app.init(hPrevInstance, pCmdLine, nCmdShow, hints);
	app.run();
	app.terminate();
	return 0;
}
