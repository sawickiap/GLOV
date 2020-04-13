#pragma once

#include "WindowConfig.h"
#include <string>

class ApplicationWin32;

class Window
{
	friend class ApplicationWin32;

protected:
	std::string	mTitle;
	int32_t		mWindowPosX;
	int32_t		mWindowPosY;
	uint32_t	mWidthWindow;
	uint32_t	mHeightWindow;
	uint32_t	mWidthBorder;
	uint32_t	mHeightBorder;
	uint32_t	mWidthWithBorder;
	uint32_t	mHeightWithBorder;
	union
	{
		struct Flag
		{
			mutable uint32_t closed			: 1;
			mutable uint32_t visible		: 1;
			mutable uint32_t maximalized	: 1;
			mutable uint32_t minimalized	: 1;
			mutable uint32_t fullscreen		: 1;
			mutable uint32_t focused		: 1;
			mutable uint32_t decorated		: 1;
			mutable uint32_t resizable		: 1;
			mutable uint32_t floating		: 1;
		} mFlag;
		mutable uint32_t mAllBits;
	};
public:
	Window() = default;
	Window(WindowConfig config);

	virtual bool create() = 0;
	virtual void minimize() = 0;
	virtual void restore() = 0;
	virtual void maximize() = 0;
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void focus() = 0;

	bool isClosed() const
	{
		return mFlag.closed != 0;
	}

	uint32_t getWindowWidth() const
	{
		return mWidthWindow;
	}
	uint32_t getWindowHeight() const
	{
		return mHeightWindow;
	}
	std::pair<uint32_t, uint32_t> getWindowSize() const
	{
		return { mWidthWindow, mHeightWindow };
	}
	std::pair<uint32_t, uint32_t> getBorderSize() const
	{
		return { mWidthBorder, mHeightBorder };
	}
	std::pair<uint32_t, uint32_t> getWindowWithBorderSize() const
	{
		return { mWidthWithBorder, mHeightWithBorder };
	}
};
