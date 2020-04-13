#include <GLOV/PhysicalDevice.h>
#include <array>

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

Result PhysicalDevice::init(VkPhysicalDevice desc)
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
	vkGetPhysicalDeviceProperties(mPhysicalDevice, &mPhysicalDeviceProperties);
	uint32_t queueFamilyPropertyCount;
	vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &queueFamilyPropertyCount, nullptr);
	mQueueFamilyProperties.resize(queueFamilyPropertyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &queueFamilyPropertyCount, mQueueFamilyProperties.data());
	vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &mMemoryProperties);
	vkGetPhysicalDeviceFeatures(mPhysicalDevice, &mFeatures);
	return Result::Success;
}

uint32_t PhysicalDevice::getQueueFamilyIndex(VkQueueFlagBits queueFlags)
{
	if (queueFlags & VK_QUEUE_COMPUTE_BIT)
	{
		for (size_t i = 0; i < mQueueFamilyProperties.size(); ++i)
		{
			if ((mQueueFamilyProperties[i].queueFlags & queueFlags) &&
				((mQueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0))
			{
				return static_cast<uint32_t>(i);
			}
		}
	}
	if (queueFlags & VK_QUEUE_TRANSFER_BIT)
	{
		for (size_t i = 0; i < mQueueFamilyProperties.size(); ++i)
		{
			if ((mQueueFamilyProperties[i].queueFlags & queueFlags) &&
				((mQueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0) &&
				((mQueueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) == 0))
			{
				return static_cast<uint32_t>(i);
			}
		}
	}
	for (size_t i = 0; i < mQueueFamilyProperties.size(); ++i)
	{
		if (mQueueFamilyProperties[i].queueFlags & queueFlags)
		{
			return static_cast<uint32_t>(i);
		}
	}
	return -1;
}

bool PhysicalDevice::getSupportedDepthFormat(VkFormat& depthFormat)
{
	std::array<VkFormat, 5> depthFormats = 
	{
		VK_FORMAT_D32_SFLOAT_S8_UINT,
		VK_FORMAT_D32_SFLOAT,
		VK_FORMAT_D24_UNORM_S8_UINT,
		VK_FORMAT_D16_UNORM_S8_UINT,
		VK_FORMAT_D16_UNORM
	};
	for (const VkFormat& format : depthFormats)
	{
		VkFormatProperties formatProps;
		vkGetPhysicalDeviceFormatProperties(mPhysicalDevice, format, &formatProps);
		if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
		{
			depthFormat = format;
			return true;
		}
	}
	return false;
}
