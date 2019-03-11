#include "../include/ImmediateContext.h"
#include <assert.h>
//TMP 
#pragma warning(disable: 4100)
using namespace GLOV;

void ImmediateContext::ResolvePipeline()
{

}

void ImmediateContext::ResolveDescriptor()
{

}

void ImmediateContext::BeforeDraw()
{
	ResolvePipeline();
	ResolveDescriptor();
}


void ImmediateContext::Begin()
{
}

void ImmediateContext::End()
{
}

void ImmediateContext::BeginRenderPass()
{
}

void ImmediateContext::EndRenderPass()
{
}

void ImmediateContext::BeginQuery()
{
}

void ImmediateContext::EndQuery() 
{
}

void ImmediateContext::BindUniformBuffers(uint32_t startSlot, uint32_t numBuffers, Buffer* const *ppBuffers)
{
}

void ImmediateContext::BindUniformBuffer(uint32_t slot, const Buffer* pConstantBuffer)
{
}

void ImmediateContext::BindStorageBuffers(uint32_t startSlot, uint32_t numBuffers, Buffer* const *ppBuffers)
{
}

void ImmediateContext::BindStorageBuffer(uint32_t slot, const Buffer* pBuffer)
{
}

void ImmediateContext::BindSamplers(uint32_t startSlot, uint32_t numSamplers, Sampler*const* ppSamplers)
{
}

void ImmediateContext::BindSampler(uint32_t slot, const Sampler* pSampler)
{
}

void ImmediateContext::BindTextures(uint32_t startSlot, uint32_t numTextures, Texture*const* ppTextures)
{
}

void ImmediateContext::BindTexture(uint32_t slot, const Sampler* pTexture)
{
}

void ImmediateContext::BindVertexBuffers(uint32_t startSlot, uint32_t numBuffers, Buffer* const* ppVertexBuffers, const uint32_t* pStrides, const uint32_t* pOffsets)
{
}

void ImmediateContext::BindVertexBuffer(uint32_t slot, const Buffer* pVertexBuffer, uint32_t pStride, uint32_t pOffset)
{
}

void ImmediateContext::BindIndexBuffer(const Buffer* pIndexBuffer, IndexType format, uint32_t offset)
{
}

void ImmediateContext::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
{
	BeforeDraw();
}

void ImmediateContext::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance)
{
	BeforeDraw();
}

void ImmediateContext::DrawIndirect(const Buffer* buffer, uint32_t offset, uint32_t drawCount, uint32_t stride)
{
	BeforeDraw();
}

void ImmediateContext::DrawIndirectCount(const Buffer* buffer, uint32_t offset, const Buffer* countBuffer, uint32_t countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
	BeforeDraw();
}

void ImmediateContext::PushConstants()
{
}

void ImmediateContext::BindViewports(uint32_t numViewports, const Viewport *pViewports)
{
}

void ImmediateContext::BindViewport(uint32_t slot, const Viewport& viewport)
{
}

void ImmediateContext::BindScissor(uint32_t numScissors, const Scissor* pScissors)
{
}

void ImmediateContext::BindScissor(uint32_t slot, const Scissor& scissor)
{
}

void ImmediateContext::BindInputLayout(const InputLayoutDesc *pInputLayout)
{
	assert(pInputLayout);
}

void ImmediateContext::BindPrimitiveTopology(PrimitiveTopology topology, bool primitiveRestartEnable)
{
}

void ImmediateContext::BindProgram(const Program* pProgram)
{
	assert(pProgram);
}

void ImmediateContext::BindDepthStencil(const DepthStencilStateDesc* pDepthStencil)
{
	assert(pDepthStencil);
}

void ImmediateContext::BindColorBlend(const ColorBlendStateDesc* pBlend)
{
	assert(pBlend);
}

void ImmediateContext::BindRasterizer(const RasterizationStateDesc* pRasterizer)
{
	assert(pRasterizer);
}

void ImmediateContext::BindMultisample(const MultisampleStateDesc* pMultisample)
{
	assert(pMultisample);
}

void ImmediateContext::Dispatch() 
{
}

void ImmediateContext::DispatchIndirect() 
{
}

void ImmediateContext::CopyBuffer() 
{
}

void ImmediateContext::CopyImage() 
{
}

void ImmediateContext::BlitImage() 
{
}

void ImmediateContext::CopyBufferToImage() 
{
}

void ImmediateContext::CopyImageToBuffer() 
{
}

void ImmediateContext::UpdateBuffer() 
{
}

void ImmediateContext::FillBuffer() 
{
}

void ImmediateContext::ClearColorImage() 
{
}

void ImmediateContext::ClearDepthStencilImage() 
{
}

void ImmediateContext::ClearAttachments() 
{
}

void ImmediateContext::ResolveImage() 
{
}
