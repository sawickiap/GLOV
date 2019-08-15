#include "pch.h"
#include "WindowWin32.h"
#include "ApplicationWin32.h"
#include "WindowConfig.h"

WindowWin32::WindowWin32(const ApplicationWin32& app, WindowConfig windowConfig)
	: mApp(app)
	, mWindowConfig(windowConfig)
	, mHandle(NULL)
	, mBigIcon(NULL)
	, mSmallIcon(NULL)
	, mStyle(getWindowStyle())
	, mExStyle(getWindowExStyle())
	, mWidthWithBorder(0u)
	, mHeightWithBorder(0u)
	, mWidthBorder(0u)
	, mHeightBorder(0u)
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
	mWindowConfig.xpos += mx;
	mWindowConfig.ypos += my;
	auto size = getBorderSize();
	mWidthWithBorder = mWindowConfig.width + size.first;
	mHeightWithBorder = mWindowConfig.height + size.second;
	mWidthBorder = size.first;
	mHeightBorder = size.second;
	//}
	const CHAR* title = mWindowConfig.title.c_str();
	mHandle = CreateWindowEx(mExStyle, _WNDCLASSNAME, title, mStyle, 
		mWindowConfig.xpos, mWindowConfig.ypos, mWidthWithBorder, mHeightWithBorder,
		NULL, NULL, mApp.getInstance(), this);
	if (mHandle == NULL)
	{
		//std::cerr << "Win32: Failed to create window \n";
		return false;
	}
	SetProp(mHandle, _PROPWIN, this);
	show();
	focus();
	return true;
}

void WindowWin32::minimize()
{
	ShowWindow(mHandle, SW_MINIMIZE);
}

void WindowWin32::restore()
{
	ShowWindow(mHandle, SW_RESTORE);
}

void WindowWin32::maximize()
{
	ShowWindow(mHandle, SW_MAXIMIZE);
}

void WindowWin32::show()
{
	ShowWindow(mHandle, SW_SHOW);
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

std::pair<uint32_t, uint32_t> WindowWin32::getWindowSize()
{
	RECT rect = { 0,0,0,0 };
	GetClientRect(mHandle, &rect);
	return std::pair(rect.right - rect.left, rect.bottom - rect.top);
}

std::pair<uint32_t, uint32_t> WindowWin32::getBorderSize()
{
	RECT rect = { 0,0,0,0 };
	AdjustWindowRectEx(&rect, mStyle, FALSE, mExStyle);
	return std::pair(rect.right - rect.left, rect.bottom - rect.top);
}

std::pair<uint32_t, uint32_t> WindowWin32::getWindowSizeWithBorder()
{
	RECT rect = { 0,0,0,0 };
	GetClientRect(mHandle, &rect);
	AdjustWindowRectEx(&rect, mStyle, FALSE, mExStyle);
	return std::pair(rect.right - rect.left, rect.bottom - rect.top);
}

DWORD WindowWin32::getWindowStyle() const
{
	DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	if (mWindowConfig.windowFlags & eWindowFlags::Fullscreen)
	{
		style |= WS_POPUP;
	}
	else
	{		
		if (mWindowConfig.windowFlags & eWindowFlags::Decorated)
		{
			style |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
			if (mWindowConfig.windowFlags & eWindowFlags::Resizable)
			{
				style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
			}
		}
		else
		{
			style |= WS_POPUP;
			if (mWindowConfig.windowFlags & eWindowFlags::Resizable)
			{
				style |= WS_THICKFRAME;
			}
		}
	}
	if (mWindowConfig.windowFlags & eWindowFlags::Maximized)
	{
		style |= WS_MAXIMIZE;
	}
	if (mWindowConfig.windowFlags & eWindowFlags::Minimized)
	{
		style |= WS_MINIMIZE;
	}
	return style;
}

DWORD WindowWin32::getWindowExStyle() const
{
	DWORD style = WS_EX_APPWINDOW;
	if (mWindowConfig.windowFlags & (eWindowFlags::Floating | eWindowFlags::Fullscreen))
	{
		style |= WS_EX_TOPMOST;
	}
	return style;
}
