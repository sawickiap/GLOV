#pragma once

#include <GLOV/GLOV.h>
#include <GLOV/GLOV_VK.h>
#include <vector>
#include <array>

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

	class Instance;
	class Device;
	class PhysicalDevice;

	class SwapChain
	{
		friend class Instance;

		Instance* mInstance;
		Device* mDevice;
		PhysicalDevice* mPhysicalDevice;
		VkSurfaceKHR mSurface = VK_NULL_HANDLE;
		std::vector<VkSurfaceFormatKHR> mSurfaceFormats;
		VkSwapchainKHR mSwapChain = VK_NULL_HANDLE;

		VkCommandPool mCommandPool;
		std::vector<VkCommandBuffer> mCommandBuffers;

		std::vector<VkFence> mWaitFences;
	public:
		
		uint32_t mImageCount;
		std::vector<VkImage> mImages;
		std::vector<VkImageView> mImageViews;
		uint32_t mPresentQueueIndex = UINT32_MAX;

		Result create(uint32_t& width, uint32_t& height, bool vsync = false);
		VkResult acquireNextImage(VkSemaphore presentCompleteSemaphore, uint32_t *imageIndex);
		VkResult queuePresent(VkQueue queue, uint32_t imageIndex, VkSemaphore waitSemaphore = VK_NULL_HANDLE);
		void cleanup();
	};
}
