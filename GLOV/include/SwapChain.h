#pragma once

#include "GLOV.h"
#include <windows.h>
#include <vector>
#include <array>
#include <cassert>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

namespace GLOV
{
	enum BUFFER_COUNT_HINT
	{
		SINGLE,
		DOUBLE,
		TRIPLE
	};

	struct SwapChainHint_Win
	{
		//DXGI_MODE_DESC   BufferDesc;
		HINSTANCE hinstance;
		HWND      hwnd;
		bool      vsync;
		bool      sqrb;
		bool      fullscreen;
		BUFFER_COUNT_HINT      bufferCount;
		//UINT             BufferCount;
		//DXGI_SAMPLE_DESC SampleDesc;
		//typedef struct DXGI_SAMPLE_DESC
		//{
		//	UINT Count;
		//	UINT Quality;
		//} DXGI_SAMPLE_DESC;
	};

	struct SwapChainBuffer
	{
		VkImage image;
		VkImageView view;
	};

	class SwapChain
	{
		VkInstance instance;
		VkDevice device;
		VkPhysicalDevice physicalDevice;
		VkSurfaceKHR surface;

	public:
		VkFormat colorFormat;
		VkColorSpaceKHR colorSpace;
		/** @brief Handle to the current swap chain, required for recreation */
		VkSwapchainKHR swapChain = VK_NULL_HANDLE;
		uint32_t imageCount;
		std::vector<VkImage> images;
		std::vector<SwapChainBuffer> buffers;
		/** @brief Queue family index of the detected graphics and presenting device queue */
		uint32_t queueNodeIndex = UINT32_MAX;

#if defined(VK_USE_PLATFORM_WIN32_KHR)
		void initSurface(void* platformHandle, void* platformWindow)
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
		void initSurface(ANativeWindow* window)
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
		void initSurface(wl_display *display, wl_surface *window)
#elif defined(VK_USE_PLATFORM_XCB_KHR)
		void initSurface(xcb_connection_t* connection, xcb_window_t window)
#elif (defined(VK_USE_PLATFORM_IOS_MVK) || defined(VK_USE_PLATFORM_MACOS_MVK))
		void initSurface(void* view)
#elif defined(_DIRECT2DISPLAY)
		void initSurface(uint32_t width, uint32_t height)
#endif
		{
			VkResult vkResult = VK_SUCCESS;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
			VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
			surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			surfaceCreateInfo.hinstance = (HINSTANCE)platformHandle;
			surfaceCreateInfo.hwnd = (HWND)platformWindow;
			vkResult = vkCreateWin32SurfaceKHR(instance, &surfaceCreateInfo, nullptr, &surface);
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
			VkAndroidSurfaceCreateInfoKHR surfaceCreateInfo = {};
			surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
			surfaceCreateInfo.window = window;
			vkResult = vkCreateAndroidSurfaceKHR(instance, &surfaceCreateInfo, NULL, &surface);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
			VkIOSSurfaceCreateInfoMVK surfaceCreateInfo = {};
			surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
			surfaceCreateInfo.pNext = NULL;
			surfaceCreateInfo.flags = 0;
			surfaceCreateInfo.pView = view;
			vkResult = vkCreateIOSSurfaceMVK(instance, &surfaceCreateInfo, nullptr, &surface);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
			VkMacOSSurfaceCreateInfoMVK surfaceCreateInfo = {};
			surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
			surfaceCreateInfo.pNext = NULL;
			surfaceCreateInfo.flags = 0;
			surfaceCreateInfo.pView = view;
			vkResult = vkCreateMacOSSurfaceMVK(instance, &surfaceCreateInfo, NULL, &surface);
#elif defined(_DIRECT2DISPLAY)
			createDirect2DisplaySurface(width, height);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
			VkWaylandSurfaceCreateInfoKHR surfaceCreateInfo = {};
			surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
			surfaceCreateInfo.display = display;
			surfaceCreateInfo.surface = window;
			vkResult = vkCreateWaylandSurfaceKHR(instance, &surfaceCreateInfo, nullptr, &surface);
#elif defined(VK_USE_PLATFORM_XCB_KHR)
			VkXcbSurfaceCreateInfoKHR surfaceCreateInfo = {};
			surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
			surfaceCreateInfo.connection = connection;
			surfaceCreateInfo.window = window;
			vkResult = vkCreateXcbSurfaceKHR(instance, &surfaceCreateInfo, nullptr, &surface);
#endif
			if (vkResult != VK_SUCCESS)
			{
				//exitFatal("Could not create surface!", err);
			}
			uint32_t queueCount;
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, NULL);
			assert(queueCount >= 1);
			std::vector<VkQueueFamilyProperties> queueProps(queueCount);
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, queueProps.data());
			std::vector<VkBool32> supportsPresent(queueCount);
			for (uint32_t i = 0; i < queueCount; i++)
			{
				vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &supportsPresent[i]);
			}
			uint32_t graphicsQueueNodeIndex = UINT32_MAX;
			uint32_t presentQueueNodeIndex = UINT32_MAX;
			for (uint32_t i = 0; i < queueCount; i++)
			{
				if ((queueProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0)
				{
					if (graphicsQueueNodeIndex == UINT32_MAX)
					{
						graphicsQueueNodeIndex = i;
					}

					if (supportsPresent[i] == VK_TRUE)
					{
						graphicsQueueNodeIndex = i;
						presentQueueNodeIndex = i;
						break;
					}
				}
			}
			if (presentQueueNodeIndex == UINT32_MAX)
			{
				for (uint32_t i = 0; i < queueCount; ++i)
				{
					if (supportsPresent[i] == VK_TRUE)
					{
						presentQueueNodeIndex = i;
						break;
					}
				}
			}
			if (graphicsQueueNodeIndex == UINT32_MAX || presentQueueNodeIndex == UINT32_MAX)
			{
				//exitFatal("Could not find a graphics and/or presenting queue!", -1);
			}
			if (graphicsQueueNodeIndex != presentQueueNodeIndex)
			{
				//exitFatal("Separate graphics and presenting queues are not supported yet!", -1);
			}
			queueNodeIndex = graphicsQueueNodeIndex;
			uint32_t formatCount;
			vkResult = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, NULL);
			assert(formatCount > 0);
			std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
			vkResult = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, surfaceFormats.data());
			if ((formatCount == 1) && (surfaceFormats[0].format == VK_FORMAT_UNDEFINED))
			{
				colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
				colorSpace = surfaceFormats[0].colorSpace;
			}
			else
			{
				bool found_B8G8R8A8_UNORM = false;
				for (auto&& surfaceFormat : surfaceFormats)
				{
					if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM)
					{
						colorFormat = surfaceFormat.format;
						colorSpace = surfaceFormat.colorSpace;
						found_B8G8R8A8_UNORM = true;
						break;
					}
				}
				if (!found_B8G8R8A8_UNORM)
				{
					colorFormat = surfaceFormats[0].format;
					colorSpace = surfaceFormats[0].colorSpace;
				}
			}
		}

		Result create(uint32_t& width, uint32_t& height, bool vsync = false)
		{
			VkResult vkResult = VK_SUCCESS;
			VkSwapchainKHR oldSwapchain = swapChain;
			VkSurfaceCapabilitiesKHR surfCaps;
			vkResult = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfCaps);
			if (vkResult)
			{
				return Result::VulkanError;
			}
			uint32_t presentModeCount;
			vkResult = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);
			if (vkResult)
			{
				return Result::VulkanError;
			}
			assert(presentModeCount > 0);
			std::vector<VkPresentModeKHR> presentModes(presentModeCount);
			vkResult = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, presentModes.data());
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
			swapchainCI.surface = surface;
			swapchainCI.minImageCount = desiredNumberOfSwapchainImages;
			swapchainCI.imageFormat = colorFormat;
			swapchainCI.imageColorSpace = colorSpace;
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
			vkResult = vkCreateSwapchainKHR(device, &swapchainCI, nullptr, &swapChain);
			if (vkResult)
			{
				return Result::VulkanError;
			}
			if (oldSwapchain != VK_NULL_HANDLE)
			{
				for (uint32_t i = 0; i < imageCount; i++)
				{
					vkDestroyImageView(device, buffers[i].view, nullptr);
				}
				vkDestroySwapchainKHR(device, oldSwapchain, nullptr);
			}
			vkResult = vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
			if (vkResult)
			{
				return Result::VulkanError;
			}
			images.resize(imageCount);
			vkResult = vkGetSwapchainImagesKHR(device, swapChain, &imageCount, images.data());
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
				colorAttachmentView.format = colorFormat;
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

				vkResult = vkCreateImageView(device, &colorAttachmentView, nullptr, &buffers[i].view);
				if (vkResult)
				{
					return Result::VulkanError;
				}
				return Result::Success;
			}
		}

		VkResult acquireNextImage(VkSemaphore presentCompleteSemaphore, uint32_t *imageIndex)
		{
			return vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, presentCompleteSemaphore, (VkFence)nullptr, imageIndex);
		}

		VkResult queuePresent(VkQueue queue, uint32_t imageIndex, VkSemaphore waitSemaphore = VK_NULL_HANDLE)
		{
			VkPresentInfoKHR presentInfo = {};
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.pNext = NULL;
			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = &swapChain;
			presentInfo.pImageIndices = &imageIndex;
			// Check if a wait semaphore has been specified to wait for before presenting the image
			if (waitSemaphore != VK_NULL_HANDLE)
			{
				presentInfo.pWaitSemaphores = &waitSemaphore;
				presentInfo.waitSemaphoreCount = 1;
			}
			return vkQueuePresentKHR(queue, &presentInfo);
		}

		void cleanup()
		{
			if (swapChain != VK_NULL_HANDLE)
			{
				for (uint32_t i = 0; i < imageCount; i++)
				{
					vkDestroyImageView(device, buffers[i].view, nullptr);
				}
			}
			if (surface != VK_NULL_HANDLE)
			{
				vkDestroySwapchainKHR(device, swapChain, nullptr);
				vkDestroySurfaceKHR(instance, surface, nullptr);
			}
			surface = VK_NULL_HANDLE;
			swapChain = VK_NULL_HANDLE;
		}
	};
}
