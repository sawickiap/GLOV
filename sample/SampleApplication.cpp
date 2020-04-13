#include "SampleApplication.h"
#include <Win32/PlatformWin32.h>
#include <Win32/WindowWin32.h>

using namespace GLOV;

SampleApplication::SampleApplication()
{
}

bool SampleApplication::init(PlatformWin32* platform)
{
	const WindowWin32* window = platform->getWindow(0);

	InstanceDesc instanceDesc;
	instanceDesc.mEnableValidationLayer = true;
	mInstance.init(instanceDesc);

	DeviceDesc deviceDesc;
	deviceDesc.physicalDeviceIndex = 0u;
	deviceDesc.queueTypeFlag = QUEUE_GRAPHICS;

	SwapChainDesc swapChainDesc;
	swapChainDesc.hinstance = platform->getInstance();
	swapChainDesc.hwnd = window->getHandle();
	swapChainDesc.width = window->getWindowWidth();
	swapChainDesc.height = window->getWindowHeight();

	ResultPair<Device*> result1 = mInstance.createDevice(deviceDesc);
	mDevice = result1.second;

	ResultPair<SwapChain*> result2 = mInstance.createSwapChain(swapChainDesc, deviceDesc);
	mSwapChain = result2.second;

	ResultPair<ImmediateContext*> result3 = mDevice->CreateImmediateContext();
	mImmediateContext = result3.second;
	return true;
}

void SampleApplication::deinit()
{

}

void SampleApplication::tick()
{
	mSwapChain->prepareFrame();
	mSwapChain->submitFrame();
}
