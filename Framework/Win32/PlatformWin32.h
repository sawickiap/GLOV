#pragma once

#include <memory>
#include <vector>
#include "PlatformDefWin32.h"

class Window;
class WindowWin32;
struct WindowConfig;
class Application;

class PlatformWin32
{
public:
	PlatformWin32(HINSTANCE hInstance);
	~PlatformWin32() = default;

	HINSTANCE getInstance() const;
	const WindowWin32* getWindow(size_t i) const;

	bool init(HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow);
	void setupApplication(Application* app);
	bool createWindow(const WindowConfig& hints);
	bool createContex(size_t windowIndex);
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

public:
	static PlatformWin32* Get;

protected:
	std::vector<std::shared_ptr<Window>> mWindows;

private:
	HINSTANCE mInstance;
	bool mRunning;
	bool mPaused;
	Application* mApplication;
};
