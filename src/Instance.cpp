#include "../include/Instance.h"
#include "../include/PhysicalDevice.h"
#include <vector>
#include <iostream>
#include <assert.h>

#define _UNUSED( x ) ((void)(& x ));

using namespace GLOV;

Instance::Instance()
	: m_VkInstance(VK_NULL_HANDLE)
	, mDebugReportCallback(VK_NULL_HANDLE)
{
}

Instance::~Instance()
{
	if (mDebugReportCallback != VK_NULL_HANDLE)
	{
		vkDestroyDebugReportCallbackEXT(m_VkInstance, mDebugReportCallback, nullptr);
	}
	if (m_VkInstance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(m_VkInstance, nullptr);
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
	}

	VkInstanceCreateInfo instInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
	instInfo.pApplicationInfo = &appInfo;
	instInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	instInfo.ppEnabledExtensionNames = instanceExtensions.data();
	instInfo.enabledLayerCount = static_cast<uint32_t>(instanceLayers.size());
	instInfo.ppEnabledLayerNames = instanceLayers.data();

	VkResult vkResult = vkCreateInstance(&instInfo, NULL, &m_VkInstance);
	if (vkResult != VK_SUCCESS)
	{
		return VkResultToResult(vkResult);
	}
	uint32_t physicalDeviceCount;
	vkResult = vkEnumeratePhysicalDevices(m_VkInstance, &physicalDeviceCount, nullptr);
	if (vkResult != VK_SUCCESS)
	{
		return VkResultToResult(vkResult);
	}
	std::vector<VkPhysicalDevice> tmpPhysicalDevices(physicalDeviceCount);
	mPhysicalDevices.reserve(physicalDeviceCount);
	vkResult = vkEnumeratePhysicalDevices(m_VkInstance, &physicalDeviceCount, tmpPhysicalDevices.data());
	for (VkPhysicalDevice vkPhysicalDevice : tmpPhysicalDevices)
	{
		PhysicalDevice* physicalDevice = mPhysicalDevices.emplace_back().get();
		physicalDevice->Init(vkPhysicalDevice);
	}
	if (vkResult != VK_SUCCESS)
	{
		return VkResultToResult(vkResult);
	}

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
		vkResult = vkCreateDebugReportCallbackEXT(m_VkInstance, &debugReportCallbackCreateInfo, nullptr, &mDebugReportCallback);
		if (vkResult != VK_SUCCESS)
		{
			return VkResultToResult(vkResult);
		}
	}

	vkCreateDebugReportCallbackEXT = PFN_vkCreateDebugReportCallbackEXT(vkGetInstanceProcAddr(m_VkInstance, "vkCreateDebugReportCallbackEXT"));
	vkCreateDebugUtilsMessengerEXT = PFN_vkCreateDebugUtilsMessengerEXT(vkGetInstanceProcAddr(m_VkInstance, "vkCreateDebugUtilsMessengerEXT"));
	vkDebugReportMessageEXT = PFN_vkDebugReportMessageEXT(vkGetInstanceProcAddr(m_VkInstance, "vkDebugReportMessageEXT"));
	vkDestroyDebugReportCallbackEXT = PFN_vkDestroyDebugReportCallbackEXT(vkGetInstanceProcAddr(m_VkInstance, "vkDestroyDebugReportCallbackEXT"));
	vkDestroyDebugUtilsMessengerEXT = PFN_vkDestroyDebugUtilsMessengerEXT(vkGetInstanceProcAddr(m_VkInstance, "vkDestroyDebugUtilsMessengerEXT"));
	return Result::Success;
}

ResultPair<Device*> Instance::CreateDevice(DeviceDesc desc)
{
	_UNUSED(desc);
	return { Result::VulkanError, nullptr };
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
	VkResult vkResult = vkCreateWin32SurfaceKHR(m_VkInstance, &surfaceCreateInfo, nullptr, &mSurface);
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
