#include "SampleApplication.h"
#include <Win32/PlatformWin32.h>
#include <Win32/WindowWin32.h>

using namespace GLOV;

SampleApplication::SampleApplication()
{
}

bool SampleApplication::init(PlatformWin32* platform)
{
	window = platform->getWindow(0);

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
	mImmediateContext->setSwapChain(mSwapChain);
	return true;
}

void SampleApplication::deinit()
{

}

void SampleApplication::tick()
{
	mSwapChain->prepareFrame();

	Viewport viewport;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(window->getWindowWidth());
	viewport.Height = static_cast<float>(window->getWindowHeight());
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	mImmediateContext->BindViewport(1, viewport);

	std::array color = { 0.5f, 0.5f, 0.5f, 1.0f };
	mImmediateContext->SetRenderTargets(1, &m_bufferView, nullptr);
	mImmediateContext->ClearRenderTargetView(m_bufferView.ptr(), color);
	mSwapChain->submitFrame();
}
