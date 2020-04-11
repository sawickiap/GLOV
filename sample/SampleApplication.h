#pragma once
#include "Application.h"

class SampleApplication : public Application
{
public:
	SampleApplication();

	virtual bool init() = 0;
	virtual void deinit() = 0;
	virtual void tick() = 0;
};

