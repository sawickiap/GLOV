#pragma once

#include "WindowConfig.h"
#include "PlatformWin32.h"

class ApplicationWin32;

class WindowWin32
{
	friend class ApplicationWin32;

	const ApplicationWin32&		mApp;
	WindowConfig				mWindowConfig;
	HWND						mHandle;
	HICON						mBigIcon;
	HICON						mSmallIcon;
	DWORD						mStyle;
	DWORD						mExStyle;
	int32_t						mWindowPosX;
	int32_t						mWindowPosY;
	uint32_t					mWidthWindow;
	uint32_t					mHeightWindow;
	uint32_t					mWidthBorder;
	uint32_t					mHeightBorder;
	uint32_t					mWidthWithBorder;
	uint32_t					mHeightWithBorder;
	union
	{
		struct
		{
			mutable uint32_t closed : 1;
			mutable uint32_t visible : 1;
			mutable uint32_t focused : 1;
			mutable uint32_t resizing : 1;
			mutable uint32_t maximized : 1;
			mutable uint32_t minimized : 1;
			mutable uint32_t decorated : 1;
			mutable uint32_t unusedBits : 26;
		};
		mutable uint32_t mBits;
	};
	bool mResizing;
public:
	WindowWin32(const ApplicationWin32& app, WindowConfig config);
	WindowWin32(const WindowWin32&) = delete;
	~WindowWin32();

	bool create();
	void minimize();
	void restore();
	void maximize();
	void show();
	void hide();
	void focus();

	HWND getHandle() const
	{
		return mHandle;
	}
	bool isClosed() const
	{
		return false;
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

protected:
	DWORD internalWindowStyle() const;
	DWORD internalWindowExStyle() const;
	std::pair<uint32_t, uint32_t> internalWindowSize();
	std::pair<uint32_t, uint32_t> internalBorderSize();
	std::pair<uint32_t, uint32_t> internalWindowWithBorderSize();
};
