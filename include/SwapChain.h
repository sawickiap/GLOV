#pragma once

#include "GLOV.h"
#include <vulkan/vulkan.h>
#include <windows.h>

namespace GLOV
{
	enum BUFFER_COUNT_HINT
	{
		SINGLE,
		DOUBLE,
		TRIPLE
	};

	struct SwapChainHint_Win
	{
		//DXGI_MODE_DESC   BufferDesc;
		HINSTANCE hinstance;
		HWND      hwnd;
		bool      vsync;
		bool      sqrb;
		bool      fullscreen;
		BUFFER_COUNT_HINT      bufferCount;
		//UINT             BufferCount;
		//DXGI_SAMPLE_DESC SampleDesc;
		//typedef struct DXGI_SAMPLE_DESC
		//{
		//	UINT Count;
		//	UINT Quality;
		//} DXGI_SAMPLE_DESC;
	};

	class SwapChain
	{

	};
}
