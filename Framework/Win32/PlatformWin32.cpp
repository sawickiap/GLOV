#include "PlatformWin32.h"
#include "WindowWin32.h"
#include <algorithm>
#ifdef _DEBUG
#include <iostream>
#endif

PlatformWin32* PlatformWin32::Get = nullptr;

PlatformWin32::PlatformWin32(HINSTANCE hInstance)
	: mInstance(hInstance)
	, mRunning(true)
	, mPaused(false)
	, mWindows()
{
	PlatformWin32::Get = this;
}

bool PlatformWin32::init(HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	_UNUSED(hPrevInstance);
	_UNUSED(pCmdLine);
	_UNUSED(nCmdShow);
	WNDCLASSEX wndClassEx;
	ZeroMemory(&wndClassEx, sizeof(wndClassEx));
	wndClassEx.cbSize = sizeof(wndClassEx);
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClassEx.lpfnWndProc = (WNDPROC)PlatformWin32::windowProc;
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = sizeof(void*) + sizeof(int);
	wndClassEx.hInstance = mInstance;
	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClassEx.hbrBackground = CreateSolidBrush(0x00FFFFFF);//(HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.lpszClassName = _WNDCLASSNAME;
	wndClassEx.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	if (!RegisterClassEx(&wndClassEx))
	{
		//Error( PLATFORM_ERROR, "Win32: Failed to register window class" );
		return false;
	}
	return true;
}

bool PlatformWin32::createWindow(const WindowConfig& hints)
{
	auto window = mWindows.emplace_back(std::make_shared<WindowWin32>(*this, hints));
	return window->create();
}

void PlatformWin32::terminate()
{
	UnregisterClass(_WNDCLASSNAME, GetModuleHandleW(NULL));
}

void PlatformWin32::run()
{
	while (mRunning)
	{
		if (!handleEvents())
		{
			break;
		}
		for (const auto& it : mWindows)
		{
			if (it->isClosed())
			{
				mRunning = false;
			}
		}
	}
}

void PlatformWin32::createConsole()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	FILE* newStdout = nullptr;
	FILE* newStderr = nullptr;
	errno_t err;
	err = freopen_s(&newStdout, "CONOUT$", "wt", stdout);
	err = freopen_s(&newStderr, "CONOUT$", "wt", stderr);
}

void PlatformWin32::deleteConsole()
{
	FreeConsole();
}

bool PlatformWin32::handleEvents()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

LRESULT CALLBACK PlatformWin32::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT retVal = 0;
	if (PlatformWin32::Get)
	{
		retVal = PlatformWin32::Get->handleMessage(hWnd, uMsg, wParam, lParam);
		return retVal;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT PlatformWin32::handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
	{
		char message[1024];
		if (uMsg > std::size(debugWMTab))
		{
			_snprintf_s(message, sizeof(message), "Received windows message: %p UNKNOWN (%d) -- 0x%IX, 0x%IX\n", hwnd, uMsg, wParam, lParam);
		}
		else
		{
			_snprintf_s(message, sizeof(message), "Received windows message: %p %s -- 0x%IX, 0x%IX\n", hwnd, debugWMTab[uMsg], wParam, lParam);
		}
		OutputDebugString(message);
		std::cout << message << '\n';
	}
#endif
	Window* windowProp = static_cast<Window*>(GetProp(hwnd, _PROPWIN));
	if (windowProp == nullptr)
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	//LONG eventTime = GetMessageTime();
	//double time = 0.0;
	Window* window = nullptr;
	auto it = std::find_if(mWindows.begin(), mWindows.end(),
		      [hwnd](const std::shared_ptr<Window>& w) { 
		      return static_cast<WindowWin32*>(w.get())->getHandle() == hwnd; });
	if(it != mWindows.end())
	{
		window = it->get();
	}
	LRESULT returnCode = -1;
	switch (uMsg)
	{
	case WM_SYSCOMMAND:
	{
		switch (wParam & 0xfff0)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
		{
			//if( ( window->monitor ) && ( window->monitor->suspendScreensaver ) )
			{
				return 0;
			}
		}
		case SC_KEYMENU:
		{
			return 0;
		}
		}
		break;
	}
	case WM_DESTROY:
	{
		break;
	}
	case WM_CLOSE:
	{
		//window->closed = true;
		break;
	}
	case WM_QUIT:
	{
		return wParam;
	}
	case WM_PAINT:
	{
		RECT rect;
		if (GetUpdateRect(hwnd, &rect, FALSE))
		{
			ValidateRect(hwnd, NULL);
		}
		//ValidateRect(hwnd, NULL);
		returnCode = 0;
		break;
	}
	case WM_ERASEBKGND:
	{
		return TRUE;
	}
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		break;
	}
	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		break;
	}
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_XBUTTONDOWN:
	{
		break;
	}
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_XBUTTONUP:
	{
		break;
	}
	case WM_ENTERSIZEMOVE:
		//window->resizing = true;
		break;
	case WM_EXITSIZEMOVE:
		//window->resizing = false;
		break;

	//case WM_NCACTIVATE:
	//case WM_NCPAINT:
	//{
	//	// Prevent title bar from being drawn after restoring a minimized undecorated window
	//	if (!window->decorated)
	//		return TRUE;
	//	break;
	//}
	default:
	{
		// std::cout << "handleMessage uMsg " << std::hex << uMsg << std::dec << std::endl;
		break;
	}
	}
	if (returnCode >= 0)
	{
		return returnCode;
	}
	else
	{
		return CallWindowProc(DefWindowProc, hwnd, uMsg, wParam, lParam);
	}
}

void PlatformWin32::setupConsole(std::string title)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w+", stdout);
	freopen_s(&stream, "CONOUT$", "w+", stderr);
	SetConsoleTitle(TEXT(title.c_str()));
}

void PlatformWin32::setupDPIAwareness()
{
	typedef HRESULT *(__stdcall *SetProcessDpiAwarenessFunc)(PROCESS_DPI_AWARENESS);
	HMODULE shCore = LoadLibraryA("Shcore.dll");
	if (shCore)
	{
		SetProcessDpiAwarenessFunc setProcessDpiAwareness = (SetProcessDpiAwarenessFunc)GetProcAddress(shCore, "SetProcessDpiAwareness");
		if (setProcessDpiAwareness != nullptr)
		{
			setProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
		}
		FreeLibrary(shCore);
	}
}
