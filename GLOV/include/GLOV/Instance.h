#pragma once

#include <GLOV/GLOV.h>
#include <GLOV/GLOV_VK.h>
#include <GLOV/Device.h>
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
	};

	struct DeviceDesc
	{
#if defined(VK_USE_PLATFORM_WIN32_KHR)
		HINSTANCE	hinstance;
		HWND		hwnd;
#endif
		uint32_t	physicalDeviceIndex;
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
	class Device;

	class Instance
	{
		VkInstance mVkInstance;
		std::vector<std::unique_ptr<PhysicalDevice>> mPhysicalDevices;
		std::vector<std::shared_ptr<Device>> mCreatedDevices;

		VkDebugReportCallbackEXT mDebugReportCallback;

	public:
		Instance();
		Instance(const Instance&) = delete;
		~Instance();

		Result Init(InstanceDesc desc);

		ResultPair<Device*> CreateDevice(DeviceDesc desc);

	private:

		Result CreateSurfaceWin32(DeviceDesc desc);

		PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT = nullptr;
		PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = nullptr;
		
		PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT = 0;
		PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT = 0;
		PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = 0;

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
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
