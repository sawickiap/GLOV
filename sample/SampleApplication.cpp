#include "SampleApplication.h"

using namespace GLOV;

SampleApplication::SampleApplication()
{
}

bool SampleApplication::init()
{
	mInstance.Init(InstanceDesc());

	ResultPair<Device*> result = mInstance.CreateDevice(DeviceDesc());
	mDevice = result.second;
	mImmediateContext = mDevice->CreateImmediateContext().second;
	//;
	//HRESULT hr = D3D11CreateDevice(
	//	0,                 // default adapter
	//	md3dDriverType,
	//	0,                 // no software device
	//	createDeviceFlags,
	//	0, 0,              // default feature level array
	//	D3D11_SDK_VERSION,
	//	&md3dDevice,
	//	&featureLevel,
	//	&md3dImmediateContext);


	//DXGI_SWAP_CHAIN_DESC sd;
	//sd.BufferDesc.Width = mClientWidth;
	//sd.BufferDesc.Height = mClientHeight;
	//sd.BufferDesc.RefreshRate.Numerator = 60;
	//sd.BufferDesc.RefreshRate.Denominator = 1;
	//sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	//sd.SampleDesc.Count = 1;
	//sd.SampleDesc.Quality = 0;
	//sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//sd.BufferCount = 1;
	//sd.OutputWindow = mhMainWnd;
	//sd.Windowed = true;
	//sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	//sd.Flags = 0;

	//HR(dxgiFactory->CreateSwapChain(md3dDevice, &sd, &mSwapChain));

	return true;
}

void SampleApplication::deinit()
{

}

void SampleApplication::tick()
{

}
