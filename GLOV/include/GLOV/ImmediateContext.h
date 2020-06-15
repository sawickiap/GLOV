#pragma once

#include <GLOV/GLOV.h>
#include <GLOV/ContextVulkanImpl.h>
#include <map>

namespace GLOV
{
	class SwapChain;

	class ImmediateContext
	{
		SwapChain* mSwapChain;

		std::map<uint32_t, VkPipeline> graphicsPipelineMap;
		ContextVulkanImpl impl;

		RasterizationStateDesc* currentRasterizationStateDesc = nullptr;
		MultisampleStateDesc* currentMultisampleStateDesc = nullptr;
		DepthStencilStateDesc* currentDepthStencilStateDesc = nullptr;
		ColorBlendAttachmentStateDesc* currentColorBlendAttachmentStateDesc = nullptr;
		ColorBlendStateDesc* currentColorBlendStateDesc = nullptr;
		InputLayoutDesc* currentInputLayoutDesc = nullptr;
		InputAssemblyStateDesc* currentInputAssemblyStateDesc = nullptr;
		Program* currentProgram = nullptr;

		RasterizationStateDesc* desiredRasterizationStateDesc = nullptr;
		MultisampleStateDesc* desiredMultisampleStateDesc = nullptr;
		DepthStencilStateDesc* desiredtDepthStencilStateDesc = nullptr;
		ColorBlendAttachmentStateDesc* desiredColorBlendAttachmentStateDesc = nullptr;
		ColorBlendStateDesc* desiredColorBlendStateDesc = nullptr;
		InputLayoutDesc* desiredInputLayoutDesc = nullptr;
		InputAssemblyStateDesc* desiredInputAssemblyStateDesc = nullptr;
		Program* desiredProgram = nullptr;

		void ResolvePipeline();
		void ResolveDescriptor();

		void BeforeDraw();

	public:
		void setSwapChain(SwapChain* swapChain) { mSwapChain = swapChain; }

		void Begin();
		void End();
		
		void BeginRenderPass();
		void EndRenderPass();

		void BeginQuery();
		void EndQuery();

		void BindUniformBuffers(uint32_t startSlot, uint32_t numBuffers, Buffer* const *ppBuffers);
		void BindUniformBuffer(uint32_t slot, const Buffer* pConstantBuffer);
		void BindStorageBuffers(uint32_t startSlot, uint32_t numBuffers, Buffer* const *ppBuffers);
		void BindStorageBuffer(uint32_t slot, const Buffer* pBuffer);
		void BindSamplers(uint32_t startSlot, uint32_t numSamplers, Sampler*const* ppSamplers);
		void BindSampler(uint32_t slot, const Sampler* pSampler);
		void BindTextures(uint32_t startSlot, uint32_t numTextures, Texture*const* ppTextures);
		void BindTexture(uint32_t slot, const Sampler* pTexture);

		void BindVertexBuffers(uint32_t startSlot, uint32_t numBuffers, Buffer* const* ppVertexBuffers, const uint32_t* pStrides, const uint32_t* pOffsets);
		void BindVertexBuffer(uint32_t slot, const Buffer* pVertexBuffer, uint32_t pStride, uint32_t pOffset);
		void BindIndexBuffer(const Buffer* pIndexBuffer, eIndexType format, uint32_t offset);
		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
		void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance);
		void DrawIndirect(const Buffer* buffer, uint32_t offset, uint32_t drawCount, uint32_t stride);
		void DrawIndirectCount(const Buffer* buffer, uint32_t offset, const Buffer* countBuffer, uint32_t countBufferOffset, uint32_t maxDrawCount, uint32_t stride);

		void PushConstants();

		void BindViewports(uint32_t numViewports, const Viewport *pViewports);
		void BindViewport(uint32_t slot, const Viewport& viewport);
		void BindScissor(uint32_t numScissors, const Scissor* pScissors);
		void BindScissor(uint32_t slot, const Scissor& scissor);

		void BindInputLayout(const InputLayoutDesc *pInputLayout);
		void BindPrimitiveTopology(ePrimitiveTopology topology, bool primitiveRestartEnable);
		void BindProgram(const Program* pProgram);
		void BindDepthStencil(const DepthStencilStateDesc* pDepthStencil);
		void BindColorBlend(const ColorBlendStateDesc* pBlend);
		void BindRasterizer(const RasterizationStateDesc* pRasterizer);
		void BindMultisample(const MultisampleStateDesc* pMultisample);

		void Dispatch();
		void DispatchIndirect();
		void CopyBuffer();
		void CopyImage();
		void BlitImage();
		void CopyBufferToImage();
		void CopyImageToBuffer();
		void UpdateBuffer();
		void FillBuffer();
		void ClearRenderTargetView(const RenderTargetView* pRenderTargetView, const std::array<float,4>& colorRGBA);
		void ClearDepthStencilImage();
		void ClearAttachments();
		void ResolveImage();
	};
}
