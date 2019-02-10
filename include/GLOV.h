#pragma once

namespace GLOV
{

enum class Result
{
    Success,
    InvalidCall,
    VulkanError,
    // TODO...
    Count
};

class Instance;
class Device;
class SwapChain;
class ImmediateContext;
class DeferredContext;

Result CreateInstance(Instance*& outInstance);
void DestroyInstance(Instance* instance);

} // namespace GLOV
