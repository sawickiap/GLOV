#pragma once

#include <GLOV/GLOV.h>
#include <GLOV/GLOV_VK.h>

namespace GLOV
{
	class ImmediateContext;

	class Device
	{
		friend class Instance;
	public:
		Device();
		Device(const Device&) = delete;

		ResultPair<ImmediateContext*> CreateImmediateContext();

#if defined(VK_USE_PLATFORM_WIN32_KHR)
		void initSurface(HINSTANCE platformHandle, HWND platformWindow, const Instance& instance, size_t devIndex);
#endif
	private:
		//VkInstance mInstance;
		VkDevice mDevice;
		VkPhysicalDevice mPhysicalDevice;
		VkSurfaceKHR mSurface;

		//QueueFamilyIndices mQueueFamilyIndices;
		VkQueue mGraphicsQueue;
		VkQueue mPresentQueue;
	};

}
