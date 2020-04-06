#pragma once

#include "Instance.h"

namespace GLOV
{

	class Device
	{
		friend class Instance;
	public:
		Device();
		Device(const Device&) = delete;
	private:
		VkDevice mDevice;
		//QueueFamilyIndices mQueueFamilyIndices;
		VkQueue mGraphicsQueue;
		VkQueue mPresentQueue;
	};

}
