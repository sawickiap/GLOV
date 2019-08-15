#pragma once

#include <cstdint>
#include <string>

enum eWindowFlags
{
	None		= 0,
	Resizable	= 1 << 0x0,
	Visible		= 1 << 0x1,
	Decorated	= 1 << 0x2,
	Focused		= 1 << 0x3,
	Default     = Resizable | Visible | Decorated | Focused,
	AutoIconify = 1 << 0x4,
	Floating	= 1 << 0x5,
	Minimized	= 1 << 0x6,
	Maximized	= 1 << 0x7,
	Fullscreen	= 1 << 0x8
};

struct WindowConfig
{
	eWindowFlags  windowFlags;
	uint32_t      width;
	uint32_t      height;
	int32_t       xpos;
	int32_t       ypos;
	std::string   title;

	uint32_t      minwidth;
	uint32_t      minheight;
	uint32_t      maxwidth;
	uint32_t      maxheight;

	WindowConfig()
		: windowFlags(eWindowFlags::Default)
		, width(0u)
		, height(0u)
		, xpos(0)
		, ypos(0)
		, title()
		, minwidth(0u)
		, minheight(0u)
		, maxwidth(0u)
		, maxheight(0u)
	{

	}
};
