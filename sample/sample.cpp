#include <GLOV/GLOV.h>

#include "Win32/PlatformWin32.h"
#include "WindowConfig.h"
#include "SampleApplication.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
//int main( int argc, char *argv[] )
{
    printf("Hello world!\n");

    //GLOV::Instance* instance = nullptr;
    //GLOV::Result res = GLOV::CreateInstance(instance);
    //assert(res == GLOV::Result::Success);

    //GLOV::DestroyInstance(instance);

	std::unique_ptr<SampleApplication> app = std::make_unique<SampleApplication>();

	PlatformWin32 platform(hInstance);
	platform.createConsole();
	WindowConfig hints;
	hints.width = 600;
	hints.height = 600;
	hints.title = "Test";
	//hints.windowFlags = (eWindowFlags)(eWindowFlags::Visible | eWindowFlags::FocusOnShow);
	//hints.windowFlags = ;
	platform.init(hPrevInstance, pCmdLine, nCmdShow);
	platform.createWindow(hints);
	platform.setupApplication(app.get());
	platform.run();
	platform.terminate();
	platform.deleteConsole();
	return 0;
}
