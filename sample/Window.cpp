#include "pch.h"
#include "Window.h"

Window::Window(WindowConfig config)
	: mTitle(config.title)
	, mWindowPosX(config.xpos)
	, mWindowPosY(config.ypos)
	, mWidthWindow(config.width)
	, mHeightWindow(config.height)
	, mWidthBorder(0u)
	, mHeightBorder(0u)
	, mWidthWithBorder(config.width)
	, mHeightWithBorder(config.height)
	, mBitsFlag(0u)
{
	visibleFlag = (config.windowFlags & eWindowFlags::Visible) != 0;
	focusedFlag = (config.windowFlags & eWindowFlags::FocusOnShow) != 0;
	decoratedFlag = (config.windowFlags & eWindowFlags::Decorated) != 0;
	closedFlag = false;
}
