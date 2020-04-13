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
#if defined(VK_USE_PLATFORM_WIN32_KHR)
		HINSTANCE	hinstance;
		HWND		hwnd;
#endif
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
		std::vector<std::unique_ptr<PhysicalDevice>> mPhysicalDevices;
		std::vector<Device> mCreatedDevices;
		std::vector<SwapChain> mCreatedSwapChain;

	public:
		Instance();
		Instance(const Instance&) = delete;
		~Instance();

		Result init(InstanceDesc desc);

		ResultPair<Device*> createDevice(DeviceDesc desc);

		VkInstance getInstance() const { return mInstance; }

	private:

		ResultPair<SwapChain*> createSwapChain(DeviceDesc desc);

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
