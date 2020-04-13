#pragma once

#include <GLOV/Instance.h>

namespace GLOV
{

	class PhysicalDevice
	{
		friend class Instance;

		VkPhysicalDevice mPhysicalDevice;
		VkPhysicalDeviceProperties mPhysicalDeviceProperties;
		std::vector<VkQueueFamilyProperties> mQueueFamilyProperties;
		VkPhysicalDeviceMemoryProperties mMemoryProperties;
		VkPhysicalDeviceFeatures mFeatures;
		std::vector<VkLayerProperties> mDeviceLayerProperties;
		std::vector<VkExtensionProperties> mDeviceExtensionProperties;
		std::vector<const char*> mDeviceLayers;
		std::vector<const char*> mDeviceExtensions;
		std::vector<VkDisplayPropertiesKHR> mDisplayProperties;
		std::vector<VkDisplayPlanePropertiesKHR> mDisplayPlaneProperties;

	public:
		PhysicalDevice();
		PhysicalDevice(PhysicalDevice&) = delete;
		~PhysicalDevice() = default;

		Result init(VkPhysicalDevice desc);
		uint32_t getQueueFamilyIndex(VkQueueFlagBits queueFlags);
		bool getSupportedDepthFormat(VkFormat& depthFormat);

		VkPhysicalDevice getPhysicalDevice() const { return mPhysicalDevice; }
	};

}
