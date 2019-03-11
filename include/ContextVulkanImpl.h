#pragma once

#include "GLOV.h"
#include <map>
#include <vulkan/vulkan.h>

namespace GLOV
{
	struct ContextVulkanImpl
	{
		VkPipelineLayoutCreateInfo CreateInputLayout(const InputLayout *pInputLayout;		
		VkPipelineInputAssemblyStateCreateInfo CreatePrimitiveTopology(PrimitiveTopology topology, bool primitiveRestartEnable);
		VkPipelineShaderStageCreateInfo CreateProgram(const Program* pProgram);
		VkPipelineDepthStencilStateCreateInfo CreateDepthStencil(const DepthStencilStateDesc* pDepthStencil);
		VkPipelineColorBlendStateCreateInfo CreateColorBlend(const ColorBlendStateDesc* pBlend);
		VkPipelineRasterizationStateCreateInfo CreateRasterizer(const RasterizationStateDesc* pRasterizer);
		VkPipelineMultisampleStateCreateInfo CreateMultisample(const MultisampleStateDesc* pMultisample);

		VkGraphicsPipelineCreateInfo CreatePipeline();
	};

}
