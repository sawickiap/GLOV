#include <GLOV/PhysicalDevice.h>

using namespace GLOV;

PhysicalDevice::PhysicalDevice()
	: mPhysicalDevice(VK_NULL_HANDLE)
{
}

//PhysicalDevice::~PhysicalDevice()
//{
//	if (mPhysicalDevice != VK_NULL_HANDLE)
//	{
//	}
//}

Result PhysicalDevice::Init(VkPhysicalDevice desc)
{
	mPhysicalDevice = desc;
	VkResult vkResult;
	{
		uint32_t propertyCount;
		do
		{
			std::string layerName;
			vkResult = vkEnumerateDeviceExtensionProperties(mPhysicalDevice, layerName.size() == 0 ? layerName.c_str() : nullptr, &propertyCount, nullptr);
			if ((vkResult == VK_SUCCESS) && propertyCount)
			{
				mDeviceExtensionProperties.resize(propertyCount);
				vkResult = vkEnumerateDeviceExtensionProperties(mPhysicalDevice, layerName.size() == 0 ? layerName.c_str() : nullptr, &propertyCount, mDeviceExtensionProperties.data());
			}
		} while (vkResult == VK_INCOMPLETE);
		assert(propertyCount <= mDeviceExtensionProperties.size());
		mDeviceExtensionProperties.resize(propertyCount);
		if (vkResult != VK_SUCCESS)
		{
			return VkResultToResult(vkResult);
		}
		mDeviceExtensions.resize(propertyCount);
		for (uint32_t i = 0; i < propertyCount; ++i)
		{
			mDeviceExtensions[i] = mDeviceExtensionProperties[i].extensionName;
		}
	}
	{
		uint32_t propertyCount;
		do
		{
			vkResult = vkEnumerateDeviceLayerProperties(mPhysicalDevice, &propertyCount, nullptr);
			if ((vkResult == VK_SUCCESS) && propertyCount)
			{
				mDeviceLayerProperties.resize(propertyCount);
				vkResult = vkEnumerateDeviceLayerProperties(mPhysicalDevice, &propertyCount, mDeviceLayerProperties.data());
			}
		} while (vkResult == VK_INCOMPLETE);
		assert(propertyCount <= mDeviceLayerProperties.size());
		mDeviceLayerProperties.resize(propertyCount);
		if (vkResult != VK_SUCCESS)
		{
			return VkResultToResult(vkResult);
		}
		mDeviceLayers.resize(propertyCount);
		for (uint32_t i = 0; i < propertyCount; ++i)
		{
			mDeviceLayers[i] = mDeviceLayerProperties[i].layerName;
		}
	}
	{
		vkGetPhysicalDeviceProperties(mPhysicalDevice, &mPhysicalDeviceProperties);
	}
	{
		uint32_t queueFamilyPropertyCount;
		vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &queueFamilyPropertyCount, nullptr);
		mQueueFamilyProperties.resize(queueFamilyPropertyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &queueFamilyPropertyCount, mQueueFamilyProperties.data());
	}
	{
		vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &mMemoryProperties);
	}
	{
		vkGetPhysicalDeviceFeatures(mPhysicalDevice, &mFeatures);
	}
	return Result::Success;
}