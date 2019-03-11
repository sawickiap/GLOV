#include "../include/ContextVulkanImpl.h"

using namespace GLOV;

VkPipelineLayoutCreateInfo ContextVulkanImpl::CreateInputLayout(const InputLayout *pInputLayout)
{
	VkPipelineLayoutCreateInfo info = {};
	return info;
}
VkPipelineInputAssemblyStateCreateInfo ContextVulkanImpl::CreatePrimitiveTopology(PrimitiveTopology topology, bool primitiveRestartEnable)
{
	VkPipelineInputAssemblyStateCreateInfo info = {};
	return info;
}
VkPipelineShaderStageCreateInfo ContextVulkanImpl::CreateProgram(const Program* pProgram)
{
	VkPipelineShaderStageCreateInfo info = {};
	return info;
}
VkPipelineDepthStencilStateCreateInfo ContextVulkanImpl::CreateDepthStencil(const DepthStencilStateDesc* pDepthStencil)
{
	VkPipelineDepthStencilStateCreateInfo info = {};
	return info;
}
VkPipelineColorBlendStateCreateInfo ContextVulkanImpl::CreateColorBlend(const ColorBlendStateDesc* pBlend)
{
	VkPipelineColorBlendStateCreateInfo info = {};
	return info;
}
VkPipelineRasterizationStateCreateInfo ContextVulkanImpl::CreateRasterizer(const RasterizationStateDesc* pRasterizer)
{
	VkPipelineRasterizationStateCreateInfo info = {};
	return info;
}
VkPipelineMultisampleStateCreateInfo ContextVulkanImpl::CreateMultisample(const MultisampleStateDesc* pMultisample)
{
	VkPipelineMultisampleStateCreateInfo info = {};
	return info;
}

VkGraphicsPipelineCreateInfo ContextVulkanImpl::CreatePipeline()
{
	VkGraphicsPipelineCreateInfo info = {};
	return info;
}