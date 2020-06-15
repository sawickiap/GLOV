#include <GLOV/Device.h>
#include <GLOV/ImmediateContext.h>
#include <array>

using namespace GLOV;

Device::Device()
{
}

ResultPair<ImmediateContext*> Device::CreateImmediateContext()
{
	mImmediateContexts.emplace_back(std::make_shared<ImmediateContext>());
	return { Result::VulkanError, mImmediateContexts.back().get() };
}

RenderTargetView* Device::createRenderTarget(const ImageView& view, const RenderTargetDesc& desc)
{
	std::array<VkImageView, 1> attachments;
	attachments[0] = view;

	VkFramebufferCreateInfo frameBufferCreateInfo = {};
	frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	// All frame buffers use the same renderpass setup
	frameBufferCreateInfo.renderPass = renderPass;
	frameBufferCreateInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
	frameBufferCreateInfo.pAttachments = attachments.data();
	frameBufferCreateInfo.width = desc.;
	frameBufferCreateInfo.height = height;
	frameBufferCreateInfo.layers = 1;
	// Create the framebuffer
	VkResult vkResult = vkCreateFramebuffer(mDevice, &frameBufferCreateInfo, nullptr, &frameBuffers[i]);
}
