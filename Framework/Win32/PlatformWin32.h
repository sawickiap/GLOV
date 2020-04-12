#pragma once

#include <memory>
#include <vector>
#include "PlatformDefWin32.h"

class Window;
struct WindowConfig;

class PlatformWin32
{
private:
	HINSTANCE mInstance;
	bool mRunning;
	bool mPaused;
protected:
	std::vector<std::shared_ptr<Window>> mWindows;
public:
	static PlatformWin32* Get;

public:
	PlatformWin32(HINSTANCE hInstance);
	~PlatformWin32() = default;

	HINSTANCE getInstance() const
	{
		return mInstance;
	}
		
	bool init(HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow);
	bool createWindow(const WindowConfig& hints);
	void terminate();
	void run();

	void createConsole();
	void deleteConsole();

protected:
	bool handleEvents();
	static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	void setupConsole(std::string title);
	void setupDPIAwareness();
};
