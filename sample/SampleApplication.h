#pragma once
#include "Application.h"
#include "../include/GLOV.h"
#include "../include/ImmediateContext.h"
#include "../include/Instance.h"
#include "../include/Device.h"

class SampleApplication : public Application
{
public:
	SampleApplication();

	virtual bool init() = 0;
	virtual void deinit() = 0;
	virtual void tick() = 0;

	GLOV::Instance mInstance;
	GLOV::ImmediateContext* mImmediateContext;
	GLOV::Device* mDevice;
};

