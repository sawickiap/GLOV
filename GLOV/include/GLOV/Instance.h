#pragma once

#include <GLOV/GLOV.h>
#include <GLOV/GLOV_VK.h>
#include <GLOV/Device.h>
#include <GLOV/SwapChain.h>
#include <GLOV/DebugMessage.h>
#include <vector>
#include <string>

namespace GLOV
{
	struct InstanceDesc
	{
		std::string	mApplicationName;
		uint32_t	mApplicationVersion;
		std::string	mEngineName;
		uint32_t	mEngineVersion;
		bool		mEnableValidationLayer;
		std::vector<std::string> mExtraInstanceExtensions;
		std::vector<std::string> mExtraInstanceLayers;
	};

	struct DeviceDesc
	{
		uint32_t	physicalDeviceIndex;
		eQueueType	queueTypeFlag;
	};

	struct QueueFamilyIndices
	{
		int graphicsFamily = -1;
		int presentFamily = -1;

		bool isComplete()
		{
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

	class PhysicalDevice;

	
	class Instance
	{
		VkInstance mInstance;
		std::vector<std::shared_ptr<PhysicalDevice>> mPhysicalDevices;
		std::vector<Device> mCreatedDevices;
		std::vector<SwapChain> mCreatedSwapChain;

	public:
		Instance();
		Instance(const Instance&) = delete;
		~Instance();

		VkInstance getInstance() const { return mInstance; }

		Result init(InstanceDesc desc);

		ResultPair<Device*> createDevice(const DeviceDesc& devDesc);
		ResultPair<SwapChain*> createSwapChain(const SwapChainDesc& swapDesc, const DeviceDesc& devDesc);

	private:

		DebugMessage mDebugMessage;
	};

	inline Result VkResultToResult(VkResult vkRes)
	{
		switch (vkRes)
		{
		case VK_SUCCESS: return Result::Success;
		default: return Result::VulkanError;
		}
	}
} // namespace GLOV
