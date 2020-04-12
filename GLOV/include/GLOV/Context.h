#pragma once

#include <GLOV/GLOV.h>

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

	template <class T>
	class Context
	{
		void Begin()
		{
			static_cast<T*>(this)->Begin();
		}
		void End()
		{
			static_cast<T*>(this)->End();
		}

		void SetUniformBuffers(uint32_t startSlot,uint32_t numBuffers,Buffer* const *ppBuffers)
		{
			static_cast<T*>(this)->SetUniformBuffers(startSlot, numBuffers, ppBuffers);
		}
		void SetUniformBuffer(uint32_t slot, const Buffer* pConstantBuffer)
		{
			static_cast<T*>(this)->SetUniformBuffer(slot, pConstantBuffer);
		}

		void SetStorageBuffers(uint32_t startSlot, uint32_t numBuffers, Buffer* const *ppBuffers)
		{
			static_cast<T*>(this)->SetStorageBuffers(startSlot, numBuffers, ppBuffers);
		}
		void SetStorageBuffer(uint32_t slot, const Buffer* pBuffer)
		{
			static_cast<T*>(this)->SetStorageBuffer(slot, pBuffer);
		}

		void SetSamplers(uint32_t startSlot, uint32_t numSamplers,Sampler*const* ppSamplers)
		{
			static_cast<T*>(this)->SetSamplers(startSlot, numSamplers, ppSamplers);
		}
		void SetSampler(uint32_t slot, const Sampler* pSampler)
		{
			static_cast<T*>(this)->SetSampler(slot, pSampler);
		}

		void SetTextures(uint32_t startSlot, uint32_t numTextures, Texture*const* ppTextures)
		{
			static_cast<T*>(this)->SetTextures(startSlot, numTextures, ppTextures);
		}
		void SetTexture(uint32_t slot, const Sampler* pTexture)
		{
			static_cast<T*>(this)->SetTexture(slot, pTexture);
		}

		void SetProgram(const Program* pProgram)
		{
			static_cast<T*>(this)->SetProgram(pProgram);
		}

		void BindVertexBuffers(uint32_t startSlot, uint32_t numBuffers, Buffer* const* ppVertexBuffers, const uint32_t* pStrides, const uint32_t* pOffsets)
		{
			static_cast<T*>(this)->BindVertexBuffers(startSlot, numBuffers, ppVertexBuffers, pStrides, pOffsets);
		}
		void BindVertexBuffer(uint32_t slot, const Buffer* pVertexBuffer, uint32_t pStride, uint32_t pOffset)
		{
			static_cast<T*>(this)->BindVertexBuffer(slot, pVertexBuffer, pStride, pOffset);
		}
		void BindIndexBuffer(const Buffer* pIndexBuffer, INDEX_TYPE format, uint32_t offset) 
		{
			static_cast<T*>(this)->BindIndexBuffer(pIndexBuffer, format, offset);
		}

		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
		{
			static_cast<T*>(this)->Draw(vertexCount, instanceCount, firstVertex, firstInstance);
		}
		void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance)
		{
			static_cast<T*>(this)->DrawIndexed(firstInstance, instanceCount, firstIndex, vertexOffset, firstInstance);
		}
		void DrawIndirect(const Buffer* buffer, uint32_t offset, uint32_t drawCount, uint32_t stride)
		{
			static_cast<T*>(this)->DrawIndirect(buffer, offset, drawCount, stride);
		}
		void DrawIndirectCount(const Buffer* buffer, uint32_t offset, const Buffer* countBuffer, uint32_t countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
		{
			static_cast<T*>(this)->DrawIndirectCount(buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
		}
	

		void SetInputLayout(const InputLayout *pInputLayout)
		{
			static_cast<T*>(this)->SetInputLayout(pInputLayout);
		}
		void SetPrimitiveTopology(PrimitiveTopology topology)
		{
			static_cast<T*>(this)->SetPrimitiveTopology(topology);
		}
		void SetDepthStencil(const DepthStencilStateDesc* pDepthStencil)
		{
			static_cast<T*>(this)->SetDepthStencil(pDepthStencil);
		}
		void SetBlend(const ColorBlendStateDesc* pBlend)
		{
			static_cast<T*>(this)->SetBlend(pBlend);
		}
		void SetRasterizer(const RasterizationStateDesc* pRasterizer)
		{
			static_cast<T*>(this)->SetRasterizer(pRasterizer);
		}
		void SetMultisample(const MultisampleStateDesc* pMultisample)
		{
			static_cast<T*>(this)->SetMultisample(pMultisample);
		}
	};
}
