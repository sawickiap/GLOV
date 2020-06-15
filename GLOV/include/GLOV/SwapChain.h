#pragma once

#include <GLOV/GLOV.h>
#include <GLOV/GLOV_VK.h>
#include <vector>
#include <array>

namespace GLOV
{
	enum eBufferingCount
	{
		SINGLE,
		DOUBLE,
		TRIPLE
	};

	enum eSwapImageHint
	{
		RGB,
		BGR,
		SRGB,
		FLOAT,
	};

	enum eFullscreen
	{
		OFF,
		ON,
		EXCLUSIVE
	};

	struct SwapChainDesc
	{
#if defined(VK_USE_PLATFORM_WIN32_KHR)
		HINSTANCE	hinstance = NULL;
		HWND		hwnd = NULL;
#endif
		uint32_t		width;
		uint32_t		height;
		bool			vsync = true;
		eSwapImageHint	imageHint;
		eFullscreen		fullscreenHint;
		eBufferingCount	bufferCount = DOUBLE;
		uint32_t		multiSampleCount = 1;
	};

	class Instance;
	class Device;
	class PhysicalDevice;

	class SwapChain
	{
		friend class Instance;

		Instance* mInstance;
		Device* mDevice = nullptr;
		PhysicalDevice* mPhysicalDevice = nullptr;
		VkSurfaceKHR mSurface = VK_NULL_HANDLE;
		std::vector<VkSurfaceFormatKHR> mSurfaceFormats;
		VkSwapchainKHR mSwapChain = VK_NULL_HANDLE;

		VkCommandPool mCommandPool;
		std::vector<VkCommandBuffer> mCommandBuffers;

		std::vector<VkFence> mWaitFences;
		uint32_t currentBuffer = 0;
	public:
		
		uint32_t mImageCount = 0;
		std::vector<VkImage> mImages;
		std::vector<VkImageView> mImageViews;
		uint32_t mPresentQueueIndex = UINT32_MAX;

		Result create(const SwapChainDesc& swapDesc);

		void cleanup();

		Result prepareFrame();
		Result submitFrame();
	
	protected:
		VkResult acquireNextImage(VkSemaphore presentCompleteSemaphore, uint32_t *imageIndex);
		VkResult queuePresent(VkQueue queue, uint32_t imageIndex, VkSemaphore waitSemaphore = VK_NULL_HANDLE);
	};
}
