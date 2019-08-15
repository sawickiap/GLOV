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
	uint32_t					mWidthWithBorder;
	uint32_t					mHeightWithBorder;
	uint32_t					mWidthBorder;
	uint32_t					mHeightBorder;
	union
	{
		struct
		{
			mutable uint32_t closed : 1;
			mutable uint32_t resizing : 1;
			mutable uint32_t unusedBits : 30;
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

	std::pair<uint32_t, uint32_t> getWindowSize();
	std::pair<uint32_t, uint32_t> getBorderSize();
	std::pair<uint32_t, uint32_t> getWindowSizeWithBorder();

protected:
	DWORD getWindowStyle() const;
	DWORD getWindowExStyle() const;
};
