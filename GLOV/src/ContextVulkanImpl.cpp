#include <GLOV/ContextVulkanImpl.h>

#define _UNUSED( x ) ((void)(& x ));

using namespace GLOV;

VkPipelineLayoutCreateInfo ContextVulkanImpl::CreateInputLayout(const InputLayoutDesc *pInputLayout)
{
	_UNUSED(pInputLayout);
	VkPipelineLayoutCreateInfo info = {};
	return info;
}
VkPipelineInputAssemblyStateCreateInfo ContextVulkanImpl::CreatePrimitiveTopology(ePrimitiveTopology topology, bool primitiveRestartEnable)
{
	_UNUSED(topology);
	_UNUSED(primitiveRestartEnable);
	VkPipelineInputAssemblyStateCreateInfo info = {};
	return info;
}
VkPipelineShaderStageCreateInfo ContextVulkanImpl::CreateProgram(const Program* pProgram)
{
	_UNUSED(pProgram);
	VkPipelineShaderStageCreateInfo info = {};
	return info;
}
VkPipelineDepthStencilStateCreateInfo ContextVulkanImpl::CreateDepthStencil(const DepthStencilStateDesc* pDepthStencil)
{
	_UNUSED(pDepthStencil);
	VkPipelineDepthStencilStateCreateInfo info = {};
	return info;
}
VkPipelineColorBlendStateCreateInfo ContextVulkanImpl::CreateColorBlend(const ColorBlendStateDesc* pBlend)
{
	_UNUSED(pBlend);
	VkPipelineColorBlendStateCreateInfo info = {};
	return info;
}
VkPipelineRasterizationStateCreateInfo ContextVulkanImpl::CreateRasterizer(const RasterizationStateDesc* pRasterizer)
{
	_UNUSED(pRasterizer);
	VkPipelineRasterizationStateCreateInfo info = {};
	return info;
}
VkPipelineMultisampleStateCreateInfo ContextVulkanImpl::CreateMultisample(const MultisampleStateDesc* pMultisample)
{
	_UNUSED(pMultisample);
	VkPipelineMultisampleStateCreateInfo info = {};
	return info;
}

VkGraphicsPipelineCreateInfo ContextVulkanImpl::CreatePipeline()
{
	VkGraphicsPipelineCreateInfo info = {};
	return info;
}