#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include <cassert>
#ifdef _WIN32
#ifndef VK_USE_PLATFORM_WIN32_KHR
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <windows.h>
#endif //  _WIN32
