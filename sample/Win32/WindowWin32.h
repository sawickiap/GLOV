#pragma once

#include "..\WindowConfig.h"
#include "..\Window.h"
#include "PlatformWin32.h"

class ApplicationWin32;

class WindowWin32 : public Window
{
	friend class ApplicationWin32;

	const ApplicationWin32&		mApp;
	HWND						mHandle;
	HICON						mBigIcon;
	HICON						mSmallIcon;
	DWORD						mStyle;
	DWORD						mExStyle;
public:
	WindowWin32(const ApplicationWin32& app, WindowConfig config);
	WindowWin32(const WindowWin32&) = delete;
	~WindowWin32();

	bool create() override;
	void minimize() override;
	void restore() override;
	void maximize() override;
	void show() override;
	void hide() override;
	void focus() override;

	HWND getHandle() const
	{
		return mHandle;
	}

protected:
	DWORD internalWindowStyle() const;
	DWORD internalWindowExStyle() const;
	std::pair<uint32_t, uint32_t> internalWindowSize();
	std::pair<uint32_t, uint32_t> internalBorderSize();
	std::pair<uint32_t, uint32_t> internalWindowWithBorderSize();
};
