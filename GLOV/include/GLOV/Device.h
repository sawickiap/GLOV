#pragma once

#include <GLOV/GLOV.h>
#include <GLOV/GLOV_VK.h>

namespace GLOV
{
	class PhysicalDevice;
	class ImmediateContext;

	class Device
	{
		friend class Instance;
	public:
		Device();
		//Device(const Device&) = delete;

		ResultPair<ImmediateContext*> CreateImmediateContext();

		VkDevice getDevice() const { return mDevice; }

	private:
		VkInstance mInstance;
		PhysicalDevice* mPhysicalDevice = nullptr;
		VkDevice mDevice;
		//VkSurfaceKHR mSurface;
		uint32_t mGraphicsQueueIndex = -1;
		uint32_t mComputeQueueIndex = -1;
		uint32_t mTransferQueueIndex = -1;
		VkQueue mQueue;
		VkSemaphore mPresentComplete;
		VkSemaphore mRenderComplete;
		VkSubmitInfo mSubmitInfo;
	};

}
