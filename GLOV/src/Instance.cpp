#include <GLOV/Instance.h>
#include <GLOV/PhysicalDevice.h>
#include <vector>
#include <iostream>
#include <assert.h>

#define _UNUSED( x ) ((void)(& x ));

using namespace GLOV;

Instance::Instance()
	: mVkInstance(VK_NULL_HANDLE)
	, mDebugReportCallback(VK_NULL_HANDLE)
{
}

Instance::~Instance()
{
	if (mDebugReportCallback != VK_NULL_HANDLE)
	{
		vkDestroyDebugReportCallbackEXT(mVkInstance, mDebugReportCallback, nullptr);
	}
	if (mVkInstance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(mVkInstance, nullptr);
	}
}

Result Instance::Init(InstanceDesc desc)
{
	VkApplicationInfo appInfo = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
	appInfo.pApplicationName = desc.mApplicationName.c_str();
	appInfo.applicationVersion = desc.mApplicationVersion;//VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = desc.mEngineName.c_str();
	appInfo.engineVersion = desc.mEngineVersion;//VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_1;

	std::vector<const char*> instanceExtensions;
	instanceExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	instanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

	std::vector<const char*> instanceLayers;
	if (desc.mEnableValidationLayer)
	{
		instanceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
		instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		//instanceExtensions.push_back(VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
	}

	VkInstanceCreateInfo instInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
	instInfo.pApplicationInfo = &appInfo;
	instInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	instInfo.ppEnabledExtensionNames = instanceExtensions.data();
	instInfo.enabledLayerCount = static_cast<uint32_t>(instanceLayers.size());
	instInfo.ppEnabledLayerNames = instanceLayers.data();

	VkResult vkResult = vkCreateInstance(&instInfo, NULL, &mVkInstance);
	if (vkResult != VK_SUCCESS)
	{
		return VkResultToResult(vkResult);
	}
	uint32_t physicalDeviceCount;
	vkResult = vkEnumeratePhysicalDevices(mVkInstance, &physicalDeviceCount, nullptr);
	if (vkResult != VK_SUCCESS)
	{
		return VkResultToResult(vkResult);
	}
	std::vector<VkPhysicalDevice> tmpPhysicalDevices(physicalDeviceCount);
	mPhysicalDevices.reserve(physicalDeviceCount);
	vkResult = vkEnumeratePhysicalDevices(mVkInstance, &physicalDeviceCount, tmpPhysicalDevices.data());
	for (VkPhysicalDevice vkPhysicalDevice : tmpPhysicalDevices)
	{
		PhysicalDevice* physicalDevice = mPhysicalDevices.emplace_back(std::make_unique<PhysicalDevice>()).get();
		physicalDevice->Init(vkPhysicalDevice);
	}
	if (vkResult != VK_SUCCESS)
	{
		return VkResultToResult(vkResult);
	}
	vkCreateDebugReportCallbackEXT = PFN_vkCreateDebugReportCallbackEXT(vkGetInstanceProcAddr(mVkInstance, "vkCreateDebugReportCallbackEXT"));
	vkCreateDebugUtilsMessengerEXT = PFN_vkCreateDebugUtilsMessengerEXT(vkGetInstanceProcAddr(mVkInstance, "vkCreateDebugUtilsMessengerEXT"));
	vkDebugReportMessageEXT = PFN_vkDebugReportMessageEXT(vkGetInstanceProcAddr(mVkInstance, "vkDebugReportMessageEXT"));
	vkDestroyDebugReportCallbackEXT = PFN_vkDestroyDebugReportCallbackEXT(vkGetInstanceProcAddr(mVkInstance, "vkDestroyDebugReportCallbackEXT"));
	vkDestroyDebugUtilsMessengerEXT = PFN_vkDestroyDebugUtilsMessengerEXT(vkGetInstanceProcAddr(mVkInstance, "vkDestroyDebugUtilsMessengerEXT"));
	if (desc.mEnableValidationLayer)
	{
		VkDebugReportCallbackCreateInfoEXT debugReportCallbackCreateInfo;
		debugReportCallbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		debugReportCallbackCreateInfo.pNext = nullptr;
		//debugReportCallbackCreateInfo.flags = VK_DEBUG_REPORT_FLAG_BITS_MAX_ENUM_EXT;
		debugReportCallbackCreateInfo.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT |
												VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
												VK_DEBUG_REPORT_ERROR_BIT_EXT |
												VK_DEBUG_REPORT_DEBUG_BIT_EXT;
		debugReportCallbackCreateInfo.pfnCallback = Instance::debugCallback;
		debugReportCallbackCreateInfo.pUserData = nullptr;
		vkResult = vkCreateDebugReportCallbackEXT(mVkInstance, &debugReportCallbackCreateInfo, nullptr, &mDebugReportCallback);
		if (vkResult != VK_SUCCESS)
		{
			return VkResultToResult(vkResult);
		}
	}
	return Result::Success;
}

ResultPair<Device*> Instance::CreateDevice(DeviceDesc desc)
{
	VkResult vkResult = VK_SUCCESS;
	VkSurfaceKHR surface;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hinstance = desc.hinstance;
	surfaceCreateInfo.hwnd = desc.hwnd;
	vkResult = vkCreateWin32SurfaceKHR(mVkInstance, &surfaceCreateInfo, nullptr, &surface);
#endif
	if (vkResult != VK_SUCCESS)
	{
		return { Result::VulkanError, nullptr };
	}
	VkPhysicalDevice physicalDevice = mPhysicalDevices[desc.physicalDeviceIndex]->GetPhysicalDevice();
	uint32_t queueCount;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, NULL);
	assert(queueCount >= 1);
	std::vector<VkQueueFamilyProperties> queueProps(queueCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, queueProps.data());
	std::vector<VkBool32> supportsPresent(queueCount);
	for (uint32_t i = 0; i < queueCount; i++)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &supportsPresent[i]);
	}
	uint32_t graphicsQueueNodeIndex = UINT32_MAX;
	uint32_t presentQueueNodeIndex = UINT32_MAX;
	for (uint32_t i = 0; i < queueCount; i++)
	{
		if ((queueProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0)
		{
			if (graphicsQueueNodeIndex == UINT32_MAX)
			{
				graphicsQueueNodeIndex = i;
			}

			if (supportsPresent[i] == VK_TRUE)
			{
				graphicsQueueNodeIndex = i;
				presentQueueNodeIndex = i;
				break;
			}
		}
	}
	if (presentQueueNodeIndex == UINT32_MAX)
	{
		for (uint32_t i = 0; i < queueCount; ++i)
		{
			if (supportsPresent[i] == VK_TRUE)
			{
				presentQueueNodeIndex = i;
				break;
			}
		}
	}
	if (graphicsQueueNodeIndex == UINT32_MAX || presentQueueNodeIndex == UINT32_MAX)
	{
		return { Result::VulkanError, nullptr };
	}
	if (graphicsQueueNodeIndex != presentQueueNodeIndex)
	{
		return { Result::VulkanError, nullptr };
	}
	uint32_t queueNodeIndex = graphicsQueueNodeIndex;
	uint32_t formatCount;
	vkResult = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, NULL);
	assert(formatCount > 0);
	std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
	vkResult = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, surfaceFormats.data());
	if (graphicsQueueNodeIndex != presentQueueNodeIndex)
	{
		return { Result::VulkanError, nullptr };
	}
	auto device = mCreatedDevices.emplace_back(std::make_shared<Device>());
	return { Result::Success, device.get() };
}

Result Instance::CreateSurfaceWin32(DeviceDesc desc)
{
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo;
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.pNext = nullptr;
	surfaceCreateInfo.flags = 0;
	surfaceCreateInfo.hinstance = desc.hinstance;
	surfaceCreateInfo.hwnd = desc.hwnd;

	VkSurfaceKHR mSurface;
	VkResult vkResult = vkCreateWin32SurfaceKHR(mVkInstance, &surfaceCreateInfo, nullptr, &mSurface);
	if (vkResult != VK_SUCCESS)
	{
		return VkResultToResult(vkResult);
	}

	VkSurfaceCapabilitiesKHR mSurfaceCapabilities;
	const VkPhysicalDevice& physicalDevice = mPhysicalDevices[desc.physicalDeviceIndex]->mPhysicalDevice;
	vkResult = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, mSurface, &mSurfaceCapabilities);
	uint32_t presentModeCount = 0;
	std::vector<VkPresentModeKHR> mSurfacePresentModes;
	do
	{
		vkResult = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, mSurface, &presentModeCount, nullptr);
		if ((vkResult == VK_SUCCESS) && presentModeCount)
		{
			mSurfacePresentModes.resize(presentModeCount);
			vkResult = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, mSurface, &presentModeCount, mSurfacePresentModes.data());
		}
	} while (vkResult == VK_INCOMPLETE);
	assert(presentModeCount <= mSurfacePresentModes.size());
	if (vkResult != VK_SUCCESS)
	{
		return VkResultToResult(vkResult);
	}
	uint32_t surfaceFormatCount;
	std::vector<VkSurfaceFormatKHR> mSurfaceFormats;
	do
	{
		vkResult = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, mSurface, &surfaceFormatCount, nullptr);
		if ((vkResult == VK_SUCCESS) && surfaceFormatCount)
		{
			mSurfaceFormats.resize(surfaceFormatCount);
			vkResult = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, mSurface, &surfaceFormatCount, mSurfaceFormats.data());
		}
	} while (vkResult == VK_INCOMPLETE);
	assert(surfaceFormatCount <= mSurfaceFormats.size());
	mSurfaceFormats.resize(surfaceFormatCount);
	if (vkResult != VK_SUCCESS)
	{
		return VkResultToResult(vkResult);
	}
	return Result::Success;
}

VKAPI_ATTR VkBool32 VKAPI_CALL Instance::debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
{
	_UNUSED(userData);
	_UNUSED(code);
	_UNUSED(location);
	_UNUSED(obj);
	_UNUSED(objType);
	static const char* reportInfoNames[] =
	{
		"INFORMATION",
		"WARNING",
		"PERFORMANCE_WARNING",
		"ERROR",
		"DEBUG"
	};
	static const char* reportObjectNames[] =
	{
		"UNKNOWN",
		"INSTANCE",
		"PHYSICAL_DEVICE",
		"DEVICE",
		"QUEUE",
		"SEMAPHORE",
		"COMMAND_BUFFER",
		"FENCE",
		"DEVICE_MEMORY",
		"BUFFER",
		"IMAGE",
		"EVENT",
		"QUERY_POOL",
		"BUFFER_VIEW",
		"IMAGE_VIEW",
		"SHADER_MODULE",
		"PIPELINE_CACHE",
		"PIPELINE_LAYOUT",
		"RENDER_PASS",
		"PIPELINE",
		"DESCRIPTOR_SET_LAYOUT",
		"SAMPLER",
		"DESCRIPTOR_POOL",
		"DESCRIPTOR_SET",
		"FRAMEBUFFER",
		"COMMAND_POOL",
		"SURFACE_KHR",
		"SWAPCHAIN_KHR",
		"DEBUG_REPORT"
	};
	static size_t flagArr[] = { 0x1,0x2,0x4,0x8,0x10 };
	size_t i = *std::find(std::begin(flagArr), std::end(flagArr), flags);
	std::cout << reportInfoNames[i] << " ";
	if (std::strcmp(layerPrefix, "loader") != 0)
	{
		std::cout << "layer: " << layerPrefix << " ";
		std::cout << "msg: " << msg;
	}
	std::cout << std::endl;
	return VK_FALSE;
}
