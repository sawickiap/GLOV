#include <GLOV/SwapChain.h>
#include <GLOV/Instance.h>
#include <GLOV/PhysicalDevice.h>
#include <GLOV/Device.h>

using namespace GLOV;

Result SwapChain::create(uint32_t& width, uint32_t& height, bool vsync)
{
	VkResult vkResult = VK_SUCCESS;
	VkSwapchainKHR oldSwapchain = mSwapChain;
	VkSurfaceCapabilitiesKHR surfCaps;
	vkResult = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(mPhysicalDevice->getPhysicalDevice(), mSurface, &surfCaps);
	if (vkResult)
	{
		return Result::VulkanError;
	}
	uint32_t presentModeCount;
	vkResult = vkGetPhysicalDeviceSurfacePresentModesKHR(mPhysicalDevice->getPhysicalDevice(), mSurface, &presentModeCount, nullptr);
	if (vkResult)
	{
		return Result::VulkanError;
	}
	assert(presentModeCount > 0);
	std::vector<VkPresentModeKHR> presentModes(presentModeCount);
	vkResult = vkGetPhysicalDeviceSurfacePresentModesKHR(mPhysicalDevice->getPhysicalDevice(), mSurface, &presentModeCount, presentModes.data());
	if (vkResult)
	{
		return Result::VulkanError;
	}
	VkExtent2D swapchainExtent = {};
	if (surfCaps.currentExtent.width == (uint32_t)-1)
	{
		swapchainExtent.width = width;
		swapchainExtent.height = height;
	}
	else
	{
		swapchainExtent = surfCaps.currentExtent;
		width = surfCaps.currentExtent.width;
		height = surfCaps.currentExtent.height;
	}

	// Select a present mode for the swapchain

	// The VK_PRESENT_MODE_FIFO_KHR mode must always be present as per spec
	// This mode waits for the vertical blank ("v-sync")
	VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;

	// If v-sync is not requested, try to find a mailbox mode
	// It's the lowest latency non-tearing present mode available
	if (!vsync)
	{
		for (size_t i = 0; i < presentModeCount; i++)
		{
			if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				swapchainPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
				break;
			}
			if ((swapchainPresentMode != VK_PRESENT_MODE_MAILBOX_KHR) && (presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR))
			{
				swapchainPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
			}
		}
	}
	uint32_t desiredNumberOfSwapchainImages = surfCaps.minImageCount + 1;
	if ((surfCaps.maxImageCount > 0) && (desiredNumberOfSwapchainImages > surfCaps.maxImageCount))
	{
		desiredNumberOfSwapchainImages = surfCaps.maxImageCount;
	}
	VkSurfaceTransformFlagsKHR preTransform;
	if (surfCaps.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
	{
		preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	}
	else
	{
		preTransform = surfCaps.currentTransform;
	}
	VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	std::array<VkCompositeAlphaFlagBitsKHR, 4> compositeAlphaFlags = {
		VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
		VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
		VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
	};
	for (auto& compositeAlphaFlag : compositeAlphaFlags)
	{
		if (surfCaps.supportedCompositeAlpha & compositeAlphaFlag)
		{
			compositeAlpha = compositeAlphaFlag;
			break;
		};
	}
	VkSwapchainCreateInfoKHR swapchainCI = {};
	swapchainCI.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCI.pNext = NULL;
	swapchainCI.surface = mSurface;
	swapchainCI.minImageCount = desiredNumberOfSwapchainImages;
	swapchainCI.imageFormat = mSurfaceFormats.front().format;
	swapchainCI.imageColorSpace = mSurfaceFormats.front().colorSpace;
	swapchainCI.imageExtent = { swapchainExtent.width, swapchainExtent.height };
	swapchainCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchainCI.preTransform = (VkSurfaceTransformFlagBitsKHR)preTransform;
	swapchainCI.imageArrayLayers = 1;
	swapchainCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchainCI.queueFamilyIndexCount = 0;
	swapchainCI.pQueueFamilyIndices = nullptr;
	swapchainCI.presentMode = swapchainPresentMode;
	swapchainCI.oldSwapchain = oldSwapchain;
	swapchainCI.clipped = VK_TRUE;
	swapchainCI.compositeAlpha = compositeAlpha;
	if (surfCaps.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
	{
		swapchainCI.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
	}
	if (surfCaps.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT)
	{
		swapchainCI.imageUsage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	}
	vkResult = vkCreateSwapchainKHR(mDevice->getDevice(), &swapchainCI, nullptr, &mSwapChain);
	if (vkResult)
	{
		return Result::VulkanError;
	}
	if (oldSwapchain != VK_NULL_HANDLE)
	{
		for (uint32_t i = 0; i < imageCount; i++)
		{
			vkDestroyImageView(mDevice->getDevice(), buffers[i].view, nullptr);
		}
		vkDestroySwapchainKHR(mDevice->getDevice(), oldSwapchain, nullptr);
	}
	vkResult = vkGetSwapchainImagesKHR(mDevice->getDevice(), mSwapChain, &imageCount, nullptr);
	if (vkResult)
	{
		return Result::VulkanError;
	}
	images.resize(imageCount);
	vkResult = vkGetSwapchainImagesKHR(mDevice->getDevice(), mSwapChain, &imageCount, images.data());
	if (vkResult)
	{
		return Result::VulkanError;
	}
	buffers.resize(imageCount);
	for (uint32_t i = 0; i < imageCount; i++)
	{
		VkImageViewCreateInfo colorAttachmentView = {};
		colorAttachmentView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		colorAttachmentView.pNext = nullptr;
		colorAttachmentView.format = mSurfaceFormats.front().format;
		colorAttachmentView.components = {
			VK_COMPONENT_SWIZZLE_R,
			VK_COMPONENT_SWIZZLE_G,
			VK_COMPONENT_SWIZZLE_B,
			VK_COMPONENT_SWIZZLE_A
		};
		colorAttachmentView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		colorAttachmentView.subresourceRange.baseMipLevel = 0;
		colorAttachmentView.subresourceRange.levelCount = 1;
		colorAttachmentView.subresourceRange.baseArrayLayer = 0;
		colorAttachmentView.subresourceRange.layerCount = 1;
		colorAttachmentView.viewType = VK_IMAGE_VIEW_TYPE_2D;
		colorAttachmentView.flags = 0;

		buffers[i].image = images[i];

		colorAttachmentView.image = buffers[i].image;

		vkResult = vkCreateImageView(mDevice->getDevice(), &colorAttachmentView, nullptr, &buffers[i].view);
		if (vkResult)
		{
			return Result::VulkanError;
		}
		return Result::Success;
	}
}

VkResult SwapChain::acquireNextImage(VkSemaphore presentCompleteSemaphore, uint32_t *imageIndex)
{
	return vkAcquireNextImageKHR(mDevice->getDevice(), mSwapChain, UINT64_MAX, presentCompleteSemaphore, (VkFence)nullptr, imageIndex);
}

VkResult SwapChain::queuePresent(VkQueue queue, uint32_t imageIndex, VkSemaphore waitSemaphore)
{
	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.pNext = NULL;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &mSwapChain;
	presentInfo.pImageIndices = &imageIndex;
	// Check if a wait semaphore has been specified to wait for before presenting the image
	if (waitSemaphore != VK_NULL_HANDLE)
	{
		presentInfo.pWaitSemaphores = &waitSemaphore;
		presentInfo.waitSemaphoreCount = 1;
	}
	return vkQueuePresentKHR(queue, &presentInfo);
}

void SwapChain::cleanup()
{
	if (mSwapChain != VK_NULL_HANDLE)
	{
		for (uint32_t i = 0; i < imageCount; i++)
		{
			vkDestroyImageView(mDevice->getDevice(), buffers[i].view, nullptr);
		}
	}
	if (mSurface != VK_NULL_HANDLE)
	{
		vkDestroySwapchainKHR(mDevice->getDevice(), mSwapChain, nullptr);
		vkDestroySurfaceKHR(mInstance->getInstance(), mSurface, nullptr);
	}
	mSurface = VK_NULL_HANDLE;
	mSwapChain = VK_NULL_HANDLE;
}
