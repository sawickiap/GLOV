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
	, mAllBits(0u)
{
	mFlag.visible = (config.windowFlags & eWindowFlags::Visible) != 0;
	mFlag.focused = (config.windowFlags & eWindowFlags::FocusOnShow) != 0;
	mFlag.decorated = (config.windowFlags & eWindowFlags::Decorated) != 0;
	mFlag.closed = false;
}
