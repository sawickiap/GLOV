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
		struct
		{
			mutable uint32_t closedFlag			: 1;
			mutable uint32_t visibleFlag		: 1;
			mutable uint32_t maximalizedFlag	: 1;
			mutable uint32_t minimalizedFlag	: 1;
			mutable uint32_t fullscreenFlag		: 1;
			mutable uint32_t focusedFlag		: 1;
			mutable uint32_t decoratedFlag		: 1;
			mutable uint32_t resizableFlag		: 1;
			mutable uint32_t floatingFlag		: 1;
		};
		mutable uint32_t mBitsFlag;
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
		return closedFlag != 0;
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
