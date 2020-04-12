#include "../include/Device.h"
#include "../include/ImmediateContext.h"

using namespace GLOV;

Device::Device()
{
}

ResultPair<ImmediateContext*> Device::CreateImmediateContext()
{
	return { Result::VulkanError, nullptr };
}
