#include "../include/GLOV.h"

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

#include <vector>

namespace GLOV
{

static const bool g_EnableValidationLayer = true; // TODO

static Result VkResultToResult(VkResult vkRes)
{
    switch(vkRes)
    {
    case VK_SUCCESS: return Result::Success;
    default: return Result::VulkanError;
    }
}

////////////////////////////////////////////////////////////////////////////////
// class Instance

class Instance
{
public:
    Instance();
    Result Init();
    ~Instance();

private:
    VkInstance m_VkInstance = VK_NULL_HANDLE;
};

Instance::Instance()
{
}

Result Instance::Init()
{
    VkApplicationInfo appInfo = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
    appInfo.pApplicationName = "GLOV"; // TODO
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // TODO
    appInfo.pEngineName = "GLOV"; // TODO
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0); // TODO
    appInfo.apiVersion = VK_API_VERSION_1_1;

    std::vector<const char*> instanceExtensions;
    instanceExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
    instanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

    std::vector<const char*> instanceLayers;
    if(g_EnableValidationLayer)
    {
        instanceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
        instanceExtensions.push_back("VK_EXT_debug_report");
    }

    VkInstanceCreateInfo instInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    instInfo.pApplicationInfo = &appInfo;
    instInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
    instInfo.ppEnabledExtensionNames = instanceExtensions.data();
    instInfo.enabledLayerCount = static_cast<uint32_t>(instanceLayers.size());
    instInfo.ppEnabledLayerNames = instanceLayers.data();

    VkResult vkRes = vkCreateInstance(&instInfo, NULL, &m_VkInstance);
    if(vkRes != VK_SUCCESS)
    {
        return VkResultToResult(vkRes);
    }

    return Result::Success;
}

Instance::~Instance()
{
    if(m_VkInstance)
    {
        vkDestroyInstance(m_VkInstance, nullptr);
    }
}

Result CreateInstance(Instance*& outInstance)
{
    outInstance = new Instance();
    Result res = outInstance->Init();
    if(res != Result::Success)
    {
        delete outInstance;
        outInstance = nullptr;
    }
    return res;
}

void DestroyInstance(Instance* instance)
{
    delete instance;
}

////////////////////////////////////////////////////////////////////////////////
// class Device

class Device
{
public:

private:
};

////////////////////////////////////////////////////////////////////////////////
// class SwapChain

class SwapChain
{
public:

private:
};

////////////////////////////////////////////////////////////////////////////////
// class ImmediateContext

class ImmediateContext
{
public:

private:
};

////////////////////////////////////////////////////////////////////////////////
// class DeferredContext

class DeferredContext
{
public:

private:
};

} // namespace GLOV
