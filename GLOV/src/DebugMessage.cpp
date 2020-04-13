#include <GLOV/DebugMessage.h>

using namespace GLOV;

VKAPI_ATTR VkBool32 VKAPI_CALL DebugMessage::debugUtilsMessengerCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
	std::string prefix("");
	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
	{
		prefix = "VERBOSE: ";
	}
	else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
	{
		prefix = "INFO: ";
	}
	else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		prefix = "WARNING: ";
	}
	else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		prefix = "ERROR: ";
	}
	std::stringstream debugMessage;
	debugMessage << prefix << "[" << pCallbackData->messageIdNumber << "][" << pCallbackData->pMessageIdName << "] : " << pCallbackData->pMessage;
	if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		std::cerr << debugMessage.str() << "\n";
	}
	else
	{
		std::cout << debugMessage.str() << "\n";
	}
	fflush(stdout);
	return VK_FALSE;
}

VkResult DebugMessage::setupDebugging(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportCallbackEXT callBack)
{
	vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
	vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));

	VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCI{};
	debugUtilsMessengerCI.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	debugUtilsMessengerCI.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	debugUtilsMessengerCI.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
	debugUtilsMessengerCI.pfnUserCallback = debugUtilsMessengerCallback;
	VkResult vkResult = vkCreateDebugUtilsMessengerEXT(instance, &debugUtilsMessengerCI, nullptr, &debugUtilsMessenger);
	assert(vkResult == VK_SUCCESS);
	return vkResult;
}

void DebugMessage::freeDebugCallback(VkInstance instance)
{
	if (debugUtilsMessenger != VK_NULL_HANDLE)
	{
		vkDestroyDebugUtilsMessengerEXT(instance, debugUtilsMessenger, nullptr);
	}
}


//VKAPI_ATTR VkBool32 VKAPI_CALL Instance::debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
//{
//	_UNUSED(userData);
//	_UNUSED(code);
//	_UNUSED(location);
//	_UNUSED(obj);
//	_UNUSED(objType);
//	static const char* reportInfoNames[] =
//	{
//		"INFORMATION",
//		"WARNING",
//		"PERFORMANCE_WARNING",
//		"ERROR",
//		"DEBUG"
//	};
//	static const char* reportObjectNames[] =
//	{
//		"UNKNOWN",
//		"INSTANCE",
//		"PHYSICAL_DEVICE",
//		"DEVICE",
//		"QUEUE",
//		"SEMAPHORE",
//		"COMMAND_BUFFER",
//		"FENCE",
//		"DEVICE_MEMORY",
//		"BUFFER",
//		"IMAGE",
//		"EVENT",
//		"QUERY_POOL",
//		"BUFFER_VIEW",
//		"IMAGE_VIEW",
//		"SHADER_MODULE",
//		"PIPELINE_CACHE",
//		"PIPELINE_LAYOUT",
//		"RENDER_PASS",
//		"PIPELINE",
//		"DESCRIPTOR_SET_LAYOUT",
//		"SAMPLER",
//		"DESCRIPTOR_POOL",
//		"DESCRIPTOR_SET",
//		"FRAMEBUFFER",
//		"COMMAND_POOL",
//		"SURFACE_KHR",
//		"SWAPCHAIN_KHR",
//		"DEBUG_REPORT"
//	};
//	static size_t flagArr[] = { 0x1,0x2,0x4,0x8,0x10 };
//	size_t i = *std::find(std::begin(flagArr), std::end(flagArr), flags);
//	std::cout << reportInfoNames[i] << " ";
//	if (std::strcmp(layerPrefix, "loader") != 0)
//	{
//		std::cout << "layer: " << layerPrefix << " ";
//		std::cout << "msg: " << msg;
//	}
//	std::cout << std::endl;
//	return VK_FALSE;
//}
