#include <GLOV/Device.h>
#include <GLOV/ImmediateContext.h>

using namespace GLOV;

Device::Device()
{
}

ResultPair<ImmediateContext*> Device::CreateImmediateContext()
{
	return { Result::VulkanError, nullptr };
}
