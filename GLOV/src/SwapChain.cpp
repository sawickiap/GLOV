#include <GLOV/SwapChain.h>
#include <GLOV/Instance.h>
#include <GLOV/PhysicalDevice.h>
#include <GLOV/Device.h>

using namespace GLOV;

Result SwapChain::create(const SwapChainDesc& swapDesc)
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
	swapchainExtent.width = swapDesc.width;
	swapchainExtent.height = swapDesc.height;
	//if (surfCaps.currentExtent.width == (uint32_t)-1)
	//{
	//	swapchainExtent.width = width;
	//	swapchainExtent.height = height;
	//}
	//else
	//{
	//	swapchainExtent = surfCaps.currentExtent;
	//	width = surfCaps.currentExtent.width;
	//	height = surfCaps.currentExtent.height;
	//}

	VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;

	//if (!vsync)
	//{
	//	for (size_t i = 0; i < presentModeCount; i++)
	//	{
	//		if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
	//		{
	//			swapchainPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
	//			break;
	//		}
	//		if ((swapchainPresentMode != VK_PRESENT_MODE_MAILBOX_KHR) && (presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR))
	//		{
	//			swapchainPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	//		}
	//	}
	//}
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
	std::array<VkCompositeAlphaFlagBitsKHR, 4> compositeAlphaFlags =
	{
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
	VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
	swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCreateInfo.pNext = nullptr;
	swapchainCreateInfo.surface = mSurface;
	swapchainCreateInfo.minImageCount = desiredNumberOfSwapchainImages;
	swapchainCreateInfo.imageFormat = mSurfaceFormats.front().format;
	swapchainCreateInfo.imageColorSpace = mSurfaceFormats.front().colorSpace;
	swapchainCreateInfo.imageExtent = { swapchainExtent.width, swapchainExtent.height };
	swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchainCreateInfo.preTransform = (VkSurfaceTransformFlagBitsKHR)preTransform;
	swapchainCreateInfo.imageArrayLayers = 1;
	swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchainCreateInfo.queueFamilyIndexCount = 0;
	swapchainCreateInfo.pQueueFamilyIndices = nullptr;
	swapchainCreateInfo.presentMode = swapchainPresentMode;
	swapchainCreateInfo.oldSwapchain = oldSwapchain;
	swapchainCreateInfo.clipped = VK_TRUE;
	swapchainCreateInfo.compositeAlpha = compositeAlpha;
	if (surfCaps.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
	{
		swapchainCreateInfo.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
	}
	if (surfCaps.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT)
	{
		swapchainCreateInfo.imageUsage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	}
	vkResult = vkCreateSwapchainKHR(mDevice->getDevice(), &swapchainCreateInfo, nullptr, &mSwapChain);
	if (vkResult)
	{
		return Result::VulkanError;
	}
	if (oldSwapchain != VK_NULL_HANDLE)
	{
		for (uint32_t i = 0; i < mImageCount; i++)
		{
			vkDestroyImageView(mDevice->getDevice(), mImageViews[i], nullptr);
		}
		vkDestroySwapchainKHR(mDevice->getDevice(), oldSwapchain, nullptr);
	}
	vkResult = vkGetSwapchainImagesKHR(mDevice->getDevice(), mSwapChain, &mImageCount, nullptr);
	if (vkResult)
	{
		return Result::VulkanError;
	}
	mImages.resize(mImageCount);
	mImageViews.resize(mImageCount);
	vkResult = vkGetSwapchainImagesKHR(mDevice->getDevice(), mSwapChain, &mImageCount, mImages.data());
	if (vkResult)
	{
		return Result::VulkanError;
	}
	for (uint32_t i = 0; i < mImageCount; i++)
	{
		VkImageViewCreateInfo colorAttachmentView = {};
		colorAttachmentView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		colorAttachmentView.pNext = nullptr;
		colorAttachmentView.format = mSurfaceFormats.front().format;
		colorAttachmentView.components =
		{
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
		colorAttachmentView.image = mImages[i];
		vkResult = vkCreateImageView(mDevice->getDevice(), &colorAttachmentView, nullptr, &mImageViews[i]);
		if (vkResult)
		{
			return Result::VulkanError;
		}
		break;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VkCommandPoolCreateInfo commandPoolCreateInfo = {};
	commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolCreateInfo.queueFamilyIndex = mPresentQueueIndex;
	commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	vkResult = vkCreateCommandPool(mDevice->getDevice(), &commandPoolCreateInfo, nullptr, &mCommandPool);
	if (vkResult)
	{
		return Result::VulkanError;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	mCommandBuffers.resize(mImageCount);
	VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
	commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferAllocateInfo.commandPool = mCommandPool;
	commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferAllocateInfo.commandBufferCount = static_cast<uint32_t>(mCommandBuffers.size());
	vkResult = vkAllocateCommandBuffers(mDevice->getDevice(), &commandBufferAllocateInfo, mCommandBuffers.data());
	if (vkResult)
	{
		return Result::VulkanError;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VkFenceCreateInfo fenceCreateInfo{};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	mWaitFences.resize(mCommandBuffers.size());
	for (VkFence& fence : mWaitFences)
	{
		vkResult = vkCreateFence(mDevice->getDevice(), &fenceCreateInfo, nullptr, &fence);
		if (vkResult)
		{
			return Result::VulkanError;
		}
	}
	return Result::Success;
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
		for (uint32_t i = 0; i < mImageCount; i++)
		{
			vkDestroyImageView(mDevice->getDevice(), mImageViews[i], nullptr);
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

Result SwapChain::prepareFrame()
{
	VkResult vkResult = acquireNextImage(mDevice->getPresentComplete(), &currentBuffer);
	if ((vkResult == VK_ERROR_OUT_OF_DATE_KHR) || (vkResult == VK_SUBOPTIMAL_KHR))
	{
//		windowResize();
		return Result::Success;
	}
	else
	{
		return VkResultToResult(vkResult);
	}
}

Result SwapChain::submitFrame()
{
	VkResult vkResult = queuePresent(mDevice->getQueue(), currentBuffer, mDevice->getRenderComplete());
	if (!((vkResult == VK_SUCCESS) || (vkResult == VK_SUBOPTIMAL_KHR)))
	{
		if (vkResult == VK_ERROR_OUT_OF_DATE_KHR)
		{
			//windowResize();
			return Result::Success;
		}
		else
		{
			return VkResultToResult(vkResult);
		}
	}
	vkResult = vkQueueWaitIdle(mDevice->getQueue());
	return VkResultToResult(vkResult);
}

//VK_CHECK_RESULT(swapChain.acquireNextImage(presentCompleteSemaphore, &currentBuffer));
//VK_CHECK_RESULT(vkWaitForFences(device, 1, &waitFences[currentBuffer], VK_TRUE, UINT64_MAX));
//VK_CHECK_RESULT(vkResetFences(device, 1, &waitFences[currentBuffer]));
//VkPipelineStageFlags waitStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
//VkSubmitInfo submitInfo = {};
//submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
//submitInfo.pWaitDstStageMask = &waitStageMask;               // Pointer to the list of pipeline stages that the semaphore waits will occur at
//submitInfo.pWaitSemaphores = &presentCompleteSemaphore;      // Semaphore(s) to wait upon before the submitted command buffer starts executing
//submitInfo.waitSemaphoreCount = 1;                           // One wait semaphore
//submitInfo.pSignalSemaphores = &renderCompleteSemaphore;     // Semaphore(s) to be signaled when command buffers have completed
//submitInfo.signalSemaphoreCount = 1;                         // One signal semaphore
//submitInfo.pCommandBuffers = &drawCmdBuffers[currentBuffer]; // Command buffers(s) to execute in this batch (submission)
//submitInfo.commandBufferCount = 1;                           // One command buffer
//VK_CHECK_RESULT(vkQueueSubmit(queue, 1, &submitInfo, waitFences[currentBuffer]));
//VkResult present = swapChain.queuePresent(queue, currentBuffer, renderCompleteSemaphore);
//if (!((present == VK_SUCCESS) || (present == VK_SUBOPTIMAL_KHR)))
//{
//	VK_CHECK_RESULT(present);
//}