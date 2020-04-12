#pragma once

#include "Instance.h"

namespace GLOV
{
	class ImmediateContext;

	class Device
	{
		friend class Instance;
	public:
		Device();
		Device(const Device&) = delete;

		ResultPair<ImmediateContext*> CreateImmediateContext();

	private:
		VkDevice mDevice;
		//QueueFamilyIndices mQueueFamilyIndices;
		VkQueue mGraphicsQueue;
		VkQueue mPresentQueue;
	};

}
