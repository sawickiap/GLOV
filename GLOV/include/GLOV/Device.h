#pragma once

#include <GLOV/GLOV.h>
#include <GLOV/GLOV_VK.h>
#include <vector>
#include <memory>

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

		const VkDevice& getDevice() const { return mDevice; }
		const VkQueue& getQueue() const { return mQueue; }
		const VkSemaphore& getPresentComplete() const { return mPresentComplete; }
		const VkSemaphore& getRenderComplete() const { return mRenderComplete; }
		const VkSubmitInfo& getSubmitInfo() const { return mSubmitInfo; }

		RenderTargetView* createRenderTarget( const RenderTargetDesc& desc );

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

		std::vector<std::shared_ptr<ImmediateContext>> mImmediateContexts;
	};

}
