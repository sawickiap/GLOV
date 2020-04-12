#pragma once

class PlatformWin32;

class Application
{
	bool mRunning;
	bool mPaused;

public:
	Application();

	virtual bool init(PlatformWin32* platfor) = 0;
	virtual void deinit() = 0;
	virtual void tick() = 0;
};

