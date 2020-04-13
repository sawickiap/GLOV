#pragma once
#include "Application.h"
#include <GLOV/GLOV.h>
#include <GLOV/ImmediateContext.h>
#include <GLOV/Instance.h>
#include <GLOV/Device.h>

class SampleApplication : public Application
{
public:
	SampleApplication();

	bool init(PlatformWin32* platform) override;
	void deinit() override;
	void tick() override;

	PlatformWin32* mPlatform;

	GLOV::Instance mInstance;
	GLOV::ImmediateContext* mImmediateContext = nullptr;
	GLOV::Device* mDevice = nullptr;
	GLOV::SwapChain* mSwapChain = nullptr;
};

