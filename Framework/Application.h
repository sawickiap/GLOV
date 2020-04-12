#pragma once

class Application
{
	bool mRunning;
	bool mPaused;

public:
	Application();

	virtual bool init() = 0;
	virtual void deinit() = 0;
	virtual void tick() = 0;
};

