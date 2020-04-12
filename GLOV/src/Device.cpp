#include <GLOV/Device.h>
#include <GLOV/ImmediateContext.h>

using namespace GLOV;

Device::Device()
{
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
void Device::initSurface(HINSTANCE platformHandle, HWND platformWindow, const Instance& instance, size_t devIndex)
{
	VkResult vkResult = VK_SUCCESS;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hinstance = platformHandle;
	surfaceCreateInfo.hwnd = platformWindow;
	//vkResult = vkCreateWin32SurfaceKHR(instance., &surfaceCreateInfo, nullptr, &mSurface);
#endif
}
#endif

ResultPair<ImmediateContext*> Device::CreateImmediateContext()
{
	return { Result::VulkanError, nullptr };
}
