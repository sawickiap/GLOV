#pragma once

#include <memory>
#include <vector>
#include "PlatformWin32.h"

class Window;
struct WindowConfig;

class ApplicationWin32
{
private:
	HINSTANCE mInstance;
	bool mRunning;
	bool mPaused;
protected:
	std::vector<std::shared_ptr<Window>> mWindows;
public:
	static ApplicationWin32* Get;

public:
	ApplicationWin32(HINSTANCE hInstance);
	~ApplicationWin32() = default;

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
