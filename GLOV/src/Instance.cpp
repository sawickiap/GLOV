#include <GLOV/Instance.h>
#include <GLOV/PhysicalDevice.h>
#include <vector>
#include <iostream>
#include <algorithm>


#define _UNUSED( x ) ((void)(& x ));

using namespace GLOV;

Instance::Instance()
	: mInstance(VK_NULL_HANDLE)
{
}

Instance::~Instance()
{
	mDebugMessage.freeDebugCallback(mInstance);
	if (mInstance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(mInstance, nullptr);
	}
}

Result Instance::init(InstanceDesc desc)
{
	VkApplicationInfo applicationInfo = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
	applicationInfo.pApplicationName = desc.mApplicationName.c_str();
	applicationInfo.applicationVersion = desc.mApplicationVersion;//VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.pEngineName = desc.mEngineName.c_str();
	applicationInfo.engineVersion = desc.mEngineVersion;//VK_MAKE_VERSION(1, 0, 0);
	applicationInfo.apiVersion = VK_API_VERSION_1_1;

	std::vector<const char*> instanceExtensions;
	instanceExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
#if defined(_WIN32)
	instanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#endif
	instanceExtensions.push_back(VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME);
	instanceExtensions.push_back(VK_NV_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME);

	for (const std::string& extension : desc.mExtraInstanceExtensions)
	{
		instanceExtensions.push_back(extension.c_str());
	}

	std::vector<const char*> instanceLayers;
	if (desc.mEnableValidationLayer)
	{
		instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		std::vector<const char*> testInstanceLayers;
		testInstanceLayers.push_back("VK_LAYER_KHRONOS_validation");
		for (const std::string& layer : desc.mExtraInstanceLayers)
		{
			testInstanceLayers.push_back(layer.c_str());
		}
		uint32_t instanceLayerCount;
		vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
		std::vector<VkLayerProperties> instanceLayerProperties(instanceLayerCount);
		vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayerProperties.data());		
		for (const VkLayerProperties& layer : instanceLayerProperties)
		{
			auto it = std::find_if(testInstanceLayers.begin(), testInstanceLayers.end(),
								[&layer](const char* val) { return std::strcmp(layer.layerName, val) == 0; });
			if (it != testInstanceLayers.end())
			{
				instanceLayers.push_back(*it);
			}
		}
	}

	VkInstanceCreateInfo instanceCreateInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
	instanceCreateInfo.pApplicationInfo = &applicationInfo;
	instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
	instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(instanceLayers.size());
	instanceCreateInfo.ppEnabledLayerNames = instanceLayers.data();

	VkResult vkResult = vkCreateInstance(&instanceCreateInfo, NULL, &mInstance);
	if (vkResult != VK_SUCCESS)
	{
		return VkResultToResult(vkResult);
	}
	uint32_t physicalDeviceCount;
	vkResult = vkEnumeratePhysicalDevices(mInstance, &physicalDeviceCount, nullptr);
	if (vkResult != VK_SUCCESS)
	{
		return VkResultToResult(vkResult);
	}
	std::vector<VkPhysicalDevice> tmpPhysicalDevices(physicalDeviceCount);
	mPhysicalDevices.reserve(physicalDeviceCount);
	vkResult = vkEnumeratePhysicalDevices(mInstance, &physicalDeviceCount, tmpPhysicalDevices.data());
	for (VkPhysicalDevice vkPhysicalDevice : tmpPhysicalDevices)
	{
		PhysicalDevice* physicalDevice = mPhysicalDevices.emplace_back(std::make_shared<PhysicalDevice>()).get();
		physicalDevice->init(vkPhysicalDevice);
	}
	if (vkResult != VK_SUCCESS)
	{
		return VkResultToResult(vkResult);
	}
	if (desc.mEnableValidationLayer)
	{
		VkDebugReportFlagsEXT debugReportFlags = VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
												 VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_DEBUG_BIT_EXT;
		vkResult = mDebugMessage.setupDebugging(mInstance, debugReportFlags, VK_NULL_HANDLE);
		if (vkResult != VK_SUCCESS)
		{
			return VkResultToResult(vkResult);
		}
	}
	return Result::Success;
}

ResultPair<Device*> Instance::createDevice(const DeviceDesc& devDesc)
{
	VkResult vkResult;
	Device device;
	device.mPhysicalDevice = mPhysicalDevices[devDesc.physicalDeviceIndex].get();
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};
	const float defaultQueuePriority = 0.0f;
	if (devDesc.queueTypeFlag & VK_QUEUE_GRAPHICS_BIT)
	{
		device.mGraphicsQueueIndex = device.mPhysicalDevice->getQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);
		VkDeviceQueueCreateInfo queueInfo{};
		queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueInfo.queueFamilyIndex = device.mGraphicsQueueIndex;
		queueInfo.queueCount = 1;
		queueInfo.pQueuePriorities = &defaultQueuePriority;
		queueCreateInfos.push_back(queueInfo);
	}
	else
	{
		device.mGraphicsQueueIndex = VK_NULL_HANDLE;
	}
	if (devDesc.queueTypeFlag & VK_QUEUE_COMPUTE_BIT)
	{
		device.mComputeQueueIndex = device.mPhysicalDevice->getQueueFamilyIndex(VK_QUEUE_COMPUTE_BIT);
		if (device.mComputeQueueIndex != device.mGraphicsQueueIndex)
		{
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = device.mComputeQueueIndex;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &defaultQueuePriority;
			queueCreateInfos.push_back(queueInfo);
		}
	}
	else
	{
		device.mComputeQueueIndex = device.mGraphicsQueueIndex;
	}
	if (devDesc.queueTypeFlag & VK_QUEUE_TRANSFER_BIT)
	{
		device.mTransferQueueIndex = device.mPhysicalDevice->getQueueFamilyIndex(VK_QUEUE_TRANSFER_BIT);
		if ((device.mTransferQueueIndex != device.mGraphicsQueueIndex) &&
			(device.mTransferQueueIndex != device.mComputeQueueIndex))
		{
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = device.mTransferQueueIndex;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &defaultQueuePriority;
			queueCreateInfos.push_back(queueInfo);
		}
	}
	else
	{
		device.mTransferQueueIndex = device.mGraphicsQueueIndex;
	}
	bool useSwapChain = true;
	std::vector<const char*> deviceExtensions = device.mPhysicalDevice->mDeviceExtensions;
	auto new_end = std::remove_if(deviceExtensions.begin(), deviceExtensions.end(),
		[](const char* name)
	{
		return std::strstr(name, "_NV_") != nullptr ||
			std::strstr(name, "_NVX_") != nullptr ||
			std::strstr(name, "_AMD_") != nullptr;
	});
	deviceExtensions.erase(new_end, deviceExtensions.end());

	VkPhysicalDeviceFeatures enabledFeatures = device.mPhysicalDevice->mFeatures;
	void* pNextChain = nullptr;
	if (useSwapChain)
	{
		deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	}
	VkDeviceCreateInfo deviceCreateInfo = {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());;
	deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
	deviceCreateInfo.pEnabledFeatures = &enabledFeatures;

	VkPhysicalDeviceFeatures2 physicalDeviceFeatures2{};
	if (pNextChain)
	{
		physicalDeviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		physicalDeviceFeatures2.features = enabledFeatures;
		physicalDeviceFeatures2.pNext = pNextChain;
		deviceCreateInfo.pEnabledFeatures = nullptr;
		deviceCreateInfo.pNext = &physicalDeviceFeatures2;
	}
	if (deviceExtensions.size() > 0)
	{
		deviceCreateInfo.enabledExtensionCount = (uint32_t)deviceExtensions.size();
		deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
	}
	vkResult = vkCreateDevice(device.mPhysicalDevice->getPhysicalDevice(), &deviceCreateInfo, nullptr, &device.mDevice);
	if (vkResult != VK_SUCCESS)
	{
		return { VkResultToResult(vkResult), nullptr };
	}
	vkGetDeviceQueue(device.mDevice, device.mGraphicsQueueIndex, 0, &device.mQueue);

	VkSemaphoreCreateInfo semaphoreCreateInfo {};
	semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	vkResult = vkCreateSemaphore(device.mDevice, &semaphoreCreateInfo, nullptr, &device.mPresentComplete);
	if (vkResult != VK_SUCCESS)
	{
		return { VkResultToResult(vkResult), nullptr };
	}
	vkResult = vkCreateSemaphore(device.mDevice, &semaphoreCreateInfo, nullptr, &device.mRenderComplete);
	if (vkResult != VK_SUCCESS)
	{
		return { VkResultToResult(vkResult), nullptr };
	}
	VkPipelineStageFlags submitPipelineStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	device.mSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	device.mSubmitInfo.pWaitDstStageMask = &submitPipelineStages;
	device.mSubmitInfo.waitSemaphoreCount = 1;
	device.mSubmitInfo.pWaitSemaphores = &device.mPresentComplete;
	device.mSubmitInfo.signalSemaphoreCount = 1;
	device.mSubmitInfo.pSignalSemaphores = &device.mRenderComplete;

	mCreatedDevices.emplace_back(device);
	return { VkResultToResult(vkResult), &mCreatedDevices.back() };
}

ResultPair<SwapChain*> Instance::createSwapChain(const SwapChainDesc& swapDesc, const DeviceDesc& devDesc)
{
	VkResult vkResult;
	SwapChain swapChain;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hinstance = swapDesc.hinstance;
	surfaceCreateInfo.hwnd = swapDesc.hwnd;
	vkResult = vkCreateWin32SurfaceKHR(mInstance, &surfaceCreateInfo, nullptr, &swapChain.mSurface);
#endif
	if (vkResult != VK_SUCCESS)
	{
		return { VkResultToResult(vkResult), {} };
	}
	swapChain.mInstance = this;
	swapChain.mPhysicalDevice = mPhysicalDevices[devDesc.physicalDeviceIndex].get();
	swapChain.mDevice = &mCreatedDevices.back();
	VkPhysicalDevice physicalDevice = swapChain.mPhysicalDevice->getPhysicalDevice();
	uint32_t queueCount;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, NULL);
	assert(queueCount >= 1);
	std::vector<VkQueueFamilyProperties> queueProps(queueCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, queueProps.data());
	std::vector<VkBool32> supportsPresent(queueCount);
	for (uint32_t i = 0; i < queueCount; i++)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, swapChain.mSurface, &supportsPresent[i]);
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
		return { VkResultToResult(vkResult), {} };
	}
	if (graphicsQueueNodeIndex != presentQueueNodeIndex)
	{
		return { VkResultToResult(vkResult), {} };
	}
	swapChain.mPresentQueueIndex = graphicsQueueNodeIndex;
	uint32_t formatCount;
	vkResult = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, swapChain.mSurface, &formatCount, NULL);
	assert(formatCount > 0);
	if (formatCount == 0)
	{
		return { VkResultToResult(vkResult), {} };
	}
	swapChain.mSurfaceFormats = std::vector<VkSurfaceFormatKHR>(formatCount);
	vkResult = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, swapChain.mSurface, &formatCount, swapChain.mSurfaceFormats.data());
	if ((formatCount == 1) && (swapChain.mSurfaceFormats.front().format == VK_FORMAT_UNDEFINED))
	{
		VkSurfaceFormatKHR surfaceFormat;
		surfaceFormat.format		= VK_FORMAT_B8G8R8A8_UNORM;
		surfaceFormat.colorSpace	= swapChain.mSurfaceFormats.front().colorSpace;
		swapChain.mSurfaceFormats.insert(swapChain.mSurfaceFormats.begin(), surfaceFormat);
	}
	else
	{
		auto it = std::find_if(swapChain.mSurfaceFormats.begin(), swapChain.mSurfaceFormats.end(),
			[](const VkSurfaceFormatKHR& surfaceFormat) { return surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM; });
		if (it != swapChain.mSurfaceFormats.end() && it != swapChain.mSurfaceFormats.begin())
		{
			std::iter_swap(swapChain.mSurfaceFormats.begin(), it);
		}
	}
	swapChain.create(swapDesc);
	mCreatedSwapChain.emplace_back(swapChain);
	return { VkResultToResult(vkResult), &mCreatedSwapChain.back() };
}
