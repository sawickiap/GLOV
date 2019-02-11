#pragma once

#include "GLOV.h"

namespace GLOV
{
	class InputLayout;
	class Sampler;
	class Buffer;
	class Texture;

	class DepthStencil;
	class Blend;
	class Rasterizer;
	class Multisample;
	class Tessellation;
	class Program;
	class Viewport;
	class Scissor;

	class ImmediateContext
	{
		void Begin()
		{
		}
		void End()
		{
		}

		void BeginRenderPass()
		{
		}
		void EndRenderPass()
		{
		}

		void BeginQuery() {}
		void EndQuery() {}

		void SetUniformBuffers(uint32_t startSlot, uint32_t numBuffers, Buffer* const *ppBuffers)
		{
		}
		void SetUniformBuffer(uint32_t slot, const Buffer* pConstantBuffer)
		{
		}

		void SetStorageBuffers(uint32_t startSlot, uint32_t numBuffers, Buffer* const *ppBuffers)
		{
		}
		void SetStorageBuffer(uint32_t slot, const Buffer* pBuffer)
		{
		}

		void SetSamplers(uint32_t startSlot, uint32_t numSamplers, Sampler*const* ppSamplers)
		{
		}
		void SetSampler(uint32_t slot, const Sampler* pSampler)
		{
		}

		void SetTextures(uint32_t startSlot, uint32_t numTextures, Texture*const* ppTextures)
		{
		}
		void SetTexture(uint32_t slot, const Sampler* pTexture)
		{
		}

		void BindVertexBuffers(uint32_t startSlot, uint32_t numBuffers, Buffer* const* ppVertexBuffers, const uint32_t* pStrides, const uint32_t* pOffsets)
		{
		}
		void BindVertexBuffer(uint32_t slot, const Buffer* pVertexBuffer, uint32_t pStride, uint32_t pOffset)
		{
		}
		void BindIndexBuffer(const Buffer* pIndexBuffer, IndexType format, uint32_t offset)
		{
		}

		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
		{
		}
		void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance)
		{
		}
		void DrawIndirect(const Buffer* buffer, uint32_t offset, uint32_t drawCount, uint32_t stride)
		{
		}
		void DrawIndirectCount(const Buffer* buffer, uint32_t offset, const Buffer* countBuffer, uint32_t countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
		{
		}

		void PushConstants()
		{
		}

		void SetViewports(uint32_t numViewports, const Viewport *pViewports)
		{
		}
		void SetViewport(uint32_t slot, const Viewport& viewport)
		{
		}
		void SetScissor(uint32_t numScissors, const Scissor* pScissors)
		{
		}
		void SetScissor(uint32_t slot, const Scissor& scissor)
		{
		}

		void SetInputLayout(const InputLayout *pInputLayout)
		{
		}
		void SetPrimitiveTopology(PrimitiveTopology topology, bool primitiveRestartEnable)
		{
		}
		void SetProgram(const Program* pProgram)
		{
		}
		void SetDepthStencil(const DepthStencil* pDepthStencil)
		{
		}
		void SetBlend(const Blend *pBlend)
		{
		}
		void SetRasterizer(const Rasterizer *pRasterizer)
		{
		}
		void SetMultisample(const Multisample *pMultisample)
		{
		}




		void Dispatch() {}
		void DispatchIndirect() {}
		void CopyBuffer() {}
		void CopyImage() {}
		void BlitImage() {}
		void CopyBufferToImage() {}
		void CopyImageToBuffer() {}
		void UpdateBuffer() {}
		void FillBuffer() {}
		void ClearColorImage() {}
		void ClearDepthStencilImage() {}
		void ClearAttachments() {}
		void ResolveImage() {}





	};
}
