#pragma once

#include <GLOV/GLOV.h>
#include <GLOV/GLOV_VK.h>
#include <map>

namespace GLOV
{
	struct ContextVulkanImpl
	{
		VkPipelineLayoutCreateInfo CreateInputLayout(const InputLayoutDesc *pInputLayout);
		VkPipelineInputAssemblyStateCreateInfo CreatePrimitiveTopology(ePrimitiveTopology topology, bool primitiveRestartEnable);
		VkPipelineShaderStageCreateInfo CreateProgram(const Program* pProgram);
		VkPipelineDepthStencilStateCreateInfo CreateDepthStencil(const DepthStencilStateDesc* pDepthStencil);
		VkPipelineColorBlendStateCreateInfo CreateColorBlend(const ColorBlendStateDesc* pBlend);
		VkPipelineRasterizationStateCreateInfo CreateRasterizer(const RasterizationStateDesc* pRasterizer);
		VkPipelineMultisampleStateCreateInfo CreateMultisample(const MultisampleStateDesc* pMultisample);

		VkGraphicsPipelineCreateInfo CreatePipeline();
	};

}
