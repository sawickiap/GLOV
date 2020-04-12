#include "WindowWin32.h"
#include "PlatformWin32.h"
#include "..\WindowConfig.h"

WindowWin32::WindowWin32(const PlatformWin32& platform, WindowConfig windowConfig)
	: Window(windowConfig)
	, mPlatform(platform)
	, mHandle(NULL)
	, mBigIcon(NULL)
	, mSmallIcon(NULL)
	, mStyle(internalWindowStyle())
	, mExStyle(internalWindowExStyle())
{
}

WindowWin32::~WindowWin32()
{
	if (mHandle != NULL)
	{
		RemoveProp(mHandle, _PROPWIN);
		DestroyWindow(mHandle);
		mHandle = NULL;
	}
	if (mBigIcon != NULL)
	{
		DestroyIcon(mBigIcon);
		mBigIcon = NULL;
	}
	if (mSmallIcon != NULL)
	{
		DestroyIcon(mSmallIcon);
		mSmallIcon = NULL;
	}
}

bool WindowWin32::create()
{
	//MonitorWin32* monitor = app->getMonitors()[windowConfig.monitorIndex];
	//if (windowConfig.fullscreen == 1 || windowConfig.fullscreenWindow)
	//{
	//	monitor->getMonitorPos(windowConfig.xpos, windowConfig.ypos);
	//	VideoMode mode = monitor->getVideoMode();
	//	widthWithBorder = mode.mWidth;
	//	heightWithBorder = mode.mHeight;
	//	windowConfig.width = mode.mWidth;
	//	windowConfig.height = mode.mHeight;
	//	widthBorder = 0;
	//	heightBorder = 0;
	//}
	//else
	//{
	int32_t mx = 0;
	int32_t my = 0;
	//monitor->getMonitorPos(mx, my);
	mWindowPosX += mx;
	mWindowPosY += my;
	auto size = getBorderSize();
	mWidthBorder = size.first;
	mHeightBorder = size.second;
	mWidthWithBorder = mWidthWindow + mWidthBorder;
	mHeightWithBorder = mHeightWindow + mHeightBorder;
	//}
	const CHAR* title = mTitle.c_str();
	mHandle = CreateWindowEx(mExStyle, _WNDCLASSNAME, title, mStyle, 
		mWindowPosX, mWindowPosY, mWidthWithBorder, mHeightWithBorder,
		NULL, NULL, mPlatform.getInstance(), this);
	if (mHandle == NULL)
	{
		//std::cerr << "Win32: Failed to create window \n";
		return false;
	}
	SetProp(mHandle, _PROPWIN, this);
	if (mFlag.visible)
	{
		show();
		if (mFlag.focused)
		{
			focus();
		}
	}
	return true;
}

void WindowWin32::minimize()
{
	ShowWindow(mHandle, SW_MINIMIZE);
	mFlag.minimalized = true;
	mFlag.maximalized = false;
}

void WindowWin32::restore()
{
	ShowWindow(mHandle, SW_RESTORE);
	mFlag.minimalized = false;
	mFlag.maximalized = false;
}

void WindowWin32::maximize()
{
	ShowWindow(mHandle, SW_MAXIMIZE);
	mFlag.maximalized = true;
	mFlag.minimalized = false;
}

void WindowWin32::show()
{
	DWORD style = GetWindowLong(mHandle, GWL_EXSTYLE);
	int nCmdShow = style & WS_EX_NOACTIVATE ? SW_SHOWNOACTIVATE : SW_SHOW;
	//ShowWindow(mHandle, SW_SHOW);//SW_SHOWNA
	ShowWindow(mHandle, nCmdShow);
}

void WindowWin32::hide()
{
	ShowWindow(mHandle, SW_HIDE);
}

void WindowWin32::focus()
{
	BringWindowToTop(mHandle);
	SetForegroundWindow(mHandle);
	SetFocus(mHandle);
}

DWORD WindowWin32::internalWindowStyle() const
{
	DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	if (mFlag.fullscreen)
	{
		style |= WS_POPUP;
	}
	else
	{
		style |= WS_SYSMENU | WS_MINIMIZEBOX;
		if (mFlag.decorated)
		{
			style |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
			if (mFlag.resizable)
			{
				style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
			}
		}
		else
		{
			style |= WS_POPUP;
			if (mFlag.resizable)
			{
				style |= WS_THICKFRAME;
			}
		}
	}
	if (mFlag.maximalized)
	{
		style |= WS_MAXIMIZE;
	}
	if (mFlag.minimalized)
	{
		style |= WS_MINIMIZE;
	}
	if (mFlag.visible)
	{
		style |= WS_VISIBLE;
	}
	return style;
}

DWORD WindowWin32::internalWindowExStyle() const
{
	//WS_EX_TRANSPARENT
	//WS_EX_APPWINDOW
	//WS_EX_CLIENTEDGE
	//WS_EX_WINDOWEDGE
	//WS_EX_ACCEPTFILES
	DWORD style = WS_EX_APPWINDOW;
	if (mFlag.fullscreen || mFlag.floating)
	{
		style |= WS_EX_TOPMOST;
	}
	return style;
}

std::pair<uint32_t, uint32_t> WindowWin32::internalWindowSize()
{
	RECT rect = { 0,0,0,0 };
	GetClientRect(mHandle, &rect);
	return std::pair(rect.right - rect.left, rect.bottom - rect.top);
}

std::pair<uint32_t, uint32_t> WindowWin32::internalBorderSize()
{
	RECT rect = { 0,0,0,0 };
	AdjustWindowRectEx(&rect, mStyle, FALSE, mExStyle);
	return std::pair(rect.right - rect.left, rect.bottom - rect.top);
}

std::pair<uint32_t, uint32_t> WindowWin32::internalWindowWithBorderSize()
{
	RECT rect = { 0,0,0,0 };
	GetClientRect(mHandle, &rect);
	AdjustWindowRectEx(&rect, mStyle, FALSE, mExStyle);
	return std::pair(rect.right - rect.left, rect.bottom - rect.top);
}
