#include "../include/GLOV.h"

#define NOMINMAX
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

#pragma warning(push, 4)
#pragma warning(disable: 4127) // conditional expression is constant
#pragma warning(disable: 4100) // unreferenced formal parameter
#pragma warning(disable: 4189) // local variable is initialized but not referenced

#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"

#pragma warning(pop)

#include <vector>

namespace GLOV
{

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
