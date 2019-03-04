#pragma once

#include <cstdint>

namespace GLOV
{

enum class Result
{
    Success,
    InvalidCall,
    VulkanError,
    // TODO...
    Count
};

enum class CompareOp : uint8_t
{
	NEVER    = 0x0,
	LESS     = 0x1,
	EQUAL    = 0x2,
	LEQUAL   = 0x3,
	GREATER  = 0x4,
	NOTEQUAL = 0x5,
	GEQUAL   = 0x6,
	ALWAYS   = 0x7
};

enum class StencilOp : uint8_t
{
	KEEP            = 0x0,
	ZERO            = 0x1,
	REPLACE         = 0x2,
	INCREMENT_CLAMP = 0x3,
	DECREMENT_CLAMP = 0x4,
	INVERT          = 0x5,
	INCREMENT_WRAP  = 0x6,
	DECREMENT_WRAP  = 0x7
};

enum class PrimitiveTopology : uint8_t
{
	POINT_LIST               = 0x0,
	LINE_LIST                = 0x1,
	LINE_STRIP               = 0x2,
	TRIANGLE_LIST            = 0x3,
	TRIANGLE_STRIP           = 0x4,
	TRIANGLE_FAN             = 0x5,
	LINE_LIST_ADJACENCY      = 0x6,
	LINE_STRIP_ADJACENCY     = 0x7,
	TRIANGLE_LIST_ADJACENCY  = 0x8,
	TRIANGLE_STRIP_ADJACENCY = 0x9,
	PATCH_LIST               = 0xA,
	UNDEFINED,
	NUM_PRIMITIVE_TYPE = UNDEFINED
};

enum class IndexType : uint8_t
{
	UINT16,
	UINT32
};

enum class CullMode : uint8_t
{
	NONE       = 0x0,
	FRONT      = 0x1,
	BACK       = 0x2,
	FRONT_BACK = 0x3
};

enum class FrontFace : uint8_t
{
	COUNTER_CLOCKWISE = 0x0,
	CLOCKWISE         = 0x1
};

enum class PolygonMode : uint8_t
{
	FILL  = 0x0,
	LINE  = 0x1,
	POINT = 0x2
};

enum class LogicOp : uint8_t
{
	CLEAR         = 0x0,
	AND           = 0x1,
	AND_REVERSE   = 0x2,
	COPY          = 0x3,
	AND_INVERTED  = 0x4,
	NO_OP         = 0x5,
	XOR           = 0x6,
	OR            = 0x7,
	NOR           = 0x8,
	EQUIVALENT    = 0x9,
	INVERT        = 0xA,
	OR_REVERSE    = 0xB,
	COPY_INVERTED = 0xC,
	OR_INVERTED   = 0xD,
	NAND          = 0xE,
	SET           = 0xF
};

enum class SampleCount 
{
	COUNT_1  = 0x01,
	COUNT_2  = 0x02,
	COUNT_4  = 0x04,
	COUNT_8  = 0x08,
	COUNT_16 = 0x10,
	COUNT_32 = 0x20,
	COUNT_64 = 0x40
};

enum class BlendOp : uint8_t
{
	ADD          = 0x0,
	SUBTRACT     = 0x1,
	REV_SUBTRACT = 0x2,
	MIN          = 0x3,
	MAX          = 0x4
};

enum class BlendFactor : uint8_t
{
	ZERO                     = 0x0,
	ONE                      = 0x1,
	SRC_COLOR                = 0x2,
	ONE_MINUS_SRC_COLOR      = 0x3,
	DST_COLOR                = 0x4,
	ONE_MINUS_DST_COLOR      = 0x5,
	SRC_ALPHA                = 0x6,
	ONE_MINUS_SRC_ALPHA      = 0x7,
	DST_ALPHA                = 0x8,
	ONE_MINUS_DST_ALPHA      = 0x9,
	CONSTANT_COLOR           = 0xA,
	ONE_MINUS_CONSTANT_COLOR = 0xB,
	CONSTANT_ALPHA           = 0xC,
	ONE_MINUS_CONSTANT_ALPHA = 0xD,
	SRC_ALPHA_SATURATE       = 0xE,
	SRC1_COLOR               = 0xF,
	ONE_MINUS_SRC1_COLOR     = 0x10,
	SRC1_ALPHA               = 0x11,
	ONE_MINUS_SRC1_ALPHA     = 0x12
};

enum class BorderColor : uint8_t
{
	FLOAT_TRANSPARENT_BLACK = 0x0,
	INT_TRANSPARENT_BLACK   = 0x1,
	FLOAT_OPAQUE_BLACK      = 0x2,
	INT_OPAQUE_BLACK        = 0x3,
	FLOAT_OPAQUE_WHITE      = 0x4,
	INT_OPAQUE_WHITE        = 0x5
};

enum class ColorComponent : uint8_t
{
	R = 0x1,
	G = 0x2,
	B = 0x4,
	A = 0x8
};

enum class VertexInputRate : uint8_t
{
	VERTEX    = 0x0,
	INSTANCE  = 0x1,
	UNDEFINED,
	NUM_VERTEX_INPUT_RATE = UNDEFINED
};

enum class TextureType : uint8_t
{
	TEXTURE_1D                   = 0x0,
	TEXTURE_2D                   = 0x1,
	TEXTURE_3D                   = 0x2,
	TEXTURE_CUBE_MAP             = 0x3,
	TEXTURE_RECTANGLE            = 0x4,
	TEXTURE_1D_ARRAY             = 0x5,
	TEXTURE_2D_ARRAY             = 0x6,
	TEXTURE_CUBE_MAP_ARRAY       = 0x7,
	TEXTURE_2D_MULTISAMPLE       = 0x8,
	TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9,
	TEXTURE_BUFFER               = 0xA,
	TEXTURE_UNDEFINED,
	NUM_TEXTURE_TYPE = TEXTURE_UNDEFINED
};

enum class WrapMode : uint8_t
{
	REPEAT                 = 0x0,
	MIRRORED_REPEAT        = 0x1,
	CLAMP_TO_EDGE          = 0x2,
	MIRROR_CLAMP_TO_EDGE   = 0x3,
	CLAMP_TO_BORDER        = 0x4,
	MIRROR_CLAMP_TO_BORDER = 0x5,
	UNDEFINED,
	NUM_WRAP_MODE = UNDEFINED
};

enum class WrapCoord : uint8_t
{
	S = 0x0,
	T = 0x1,
	R = 0x2,
	UNDEFINED,
	NUM_WRAP_COORD = UNDEFINED
};

enum class MinMagFilter : uint8_t
{
	NEAREST = 0x0,
	LINEAR  = 0x1,
	UNDEFINED,
	NUM_MINMAG_FILTER = UNDEFINED
};

enum class MipmapMode : uint8_t
{
	NONE    = 0x0,
	NEAREST = 0x1,
	LINEAR  = 0x2,
	UNDEFINED,
	NUM_MIPMAP_MODE = UNDEFINED
};

enum class BufferUsage : uint16_t
{
	UNDEFINED = 0x00,
	CPU_WRITE_ONCE = 0x01,
	CPU_WRITE_RARE = 0x02,
	CPU_WRITE_OFTEN = 0x04,
	CPU_READ = 0x08,
	GPU_WRITE_ONCE = 0x10,
	GPU_WRITE_RARE = 0x20,
	GPU_WRITE_OFTEN = 0x40,
	GPU_READ = 0x80,
	CPU_STREAMING = 0x100,
	GPU_STREAMING = 0x200,
	BUFFER_WRITEBACK = GPU_WRITE_OFTEN | CPU_READ,
	BUFFER_IMMUTABLE = CPU_WRITE_ONCE | GPU_READ,
	RENDER_TARGET_TEX = GPU_WRITE_OFTEN | GPU_READ,
	BUFFER_DYNAMIC = CPU_WRITE_OFTEN | GPU_READ,
	BUFFER_DEFAULT = CPU_WRITE_RARE | GPU_READ,
};

enum class ShaderStage : uint32_t
{
	VERTEX       = 0x00000001,
	HULL         = 0x00000002,
	DOMAIN       = 0x00000004,
	GEOMETRY     = 0x00000008,
	FRAGMENT     = 0x00000010,
	COMPUTE      = 0x00000020,
	ALL_GRAPHICS = 0x0000001F,
	ALL          = 0x7FFFFFFF
};

enum class ImgBufFormat : uint16_t
{
	R3G3B2_UNORM_PACK8,
	R4G4_UNORM_PACK8,
	R4G4B4A4_UNORM_PACK16,
	B4G4R4A4_UNORM_PACK16,
	R5G6B5_UNORM_PACK16,
	B5G6R5_UNORM_PACK16,
	R5G5B5A1_UNORM_PACK16,
	B5G5R5A1_UNORM_PACK16,
	A1R5G5B5_UNORM_PACK16,
	R8_UNORM,
	R8_SNORM,
	R8_USCALED,
	R8_SSCALED,
	R8_UINT,
	R8_SINT,
	R8_SRGB,
	R8G8_UNORM,
	R8G8_SNORM,
	R8G8_USCALED,
	R8G8_SSCALED,
	R8G8_UINT,
	R8G8_SINT,
	R8G8_SRGB,
	R8G8B8_UNORM,
	R8G8B8_SNORM,
	R8G8B8_USCALED,
	R8G8B8_SSCALED,
	R8G8B8_UINT,
	R8G8B8_SINT,
	R8G8B8_SRGB,
	B8G8R8_UNORM,
	B8G8R8_SNORM,
	B8G8R8_USCALED,
	B8G8R8_SSCALED,
	B8G8R8_UINT,
	B8G8R8_SINT,
	B8G8R8_SRGB,
	R8G8B8A8_UNORM,
	R8G8B8A8_SNORM,
	R8G8B8A8_USCALED,
	R8G8B8A8_SSCALED,
	R8G8B8A8_UINT,
	R8G8B8A8_SINT,
	R8G8B8A8_SRGB,
	B8G8R8A8_UNORM,
	B8G8R8A8_SNORM,
	B8G8R8A8_USCALED,
	B8G8R8A8_SSCALED,
	B8G8R8A8_UINT,
	B8G8R8A8_SINT,
	B8G8R8A8_SRGB,
	A8B8G8R8_UNORM_PACK32,
	A8B8G8R8_SNORM_PACK32,
	A8B8G8R8_USCALED_PACK32,
	A8B8G8R8_SSCALED_PACK32,
	A8B8G8R8_UINT_PACK32,
	A8B8G8R8_SINT_PACK32,
	A8B8G8R8_SRGB_PACK32,
	A2R10G10B10_UNORM_PACK32,
	A2R10G10B10_SNORM_PACK32,
	A2R10G10B10_USCALED_PACK32,
	A2R10G10B10_SSCALED_PACK32,
	A2R10G10B10_UINT_PACK32,
	A2R10G10B10_SINT_PACK32,
	A2B10G10R10_UNORM_PACK32,
	A2B10G10R10_SNORM_PACK32,
	A2B10G10R10_USCALED_PACK32,
	A2B10G10R10_SSCALED_PACK32,
	A2B10G10R10_UINT_PACK32,
	A2B10G10R10_SINT_PACK32,
	R16_UNORM,
	R16_SNORM,
	R16_USCALED,
	R16_SSCALED,
	R16_UINT,
	R16_SINT,
	R16_SFLOAT,
	R16G16_UNORM,
	R16G16_SNORM,
	R16G16_USCALED,
	R16G16_SSCALED,
	R16G16_UINT,
	R16G16_SINT,
	R16G16_SFLOAT,
	R16G16B16_UNORM,
	R16G16B16_SNORM,
	R16G16B16_USCALED,
	R16G16B16_SSCALED,
	R16G16B16_UINT,
	R16G16B16_SINT,
	R16G16B16_SFLOAT,
	R16G16B16A16_UNORM,
	R16G16B16A16_SNORM,
	R16G16B16A16_USCALED,
	R16G16B16A16_SSCALED,
	R16G16B16A16_UINT,
	R16G16B16A16_SINT,
	R16G16B16A16_SFLOAT,
	R32_UINT,
	R32_SINT,
	R32_SFLOAT,
	R32G32_UINT,
	R32G32_SINT,
	R32G32_SFLOAT,
	R32G32B32_UINT,
	R32G32B32_SINT,
	R32G32B32_SFLOAT,
	R32G32B32A32_UINT,
	R32G32B32A32_SINT,
	R32G32B32A32_SFLOAT,
	R64_UINT,
	R64_SINT,
	R64_SFLOAT,
	R64G64_UINT,
	R64G64_SINT,
	R64G64_SFLOAT,
	R64G64B64_UINT,
	R64G64B64_SINT,
	R64G64B64_SFLOAT,
	R64G64B64A64_UINT,
	R64G64B64A64_SINT,
	R64G64B64A64_SFLOAT,
	B10G11R11_UFLOAT_PACK32,
	E5B9G9R9_UFLOAT_PACK32,

	D16_UNORM,
	D24_UNORM,
	D32_UNORM,
	D16_SFLOAT,
	D32_SFLOAT,
	S1_UINT,
	S4_UINT,
	S8_UINT,
	S16_UINT,
	D16_UNORM_S8_UINT,
	D24_UNORM_S8_UINT,
	D32_SFLOAT_S8_UINT,

	BC1_RGB_UNORM_BLOCK,
	BC1_RGB_SRGB_BLOCK,
	BC1_RGBA_UNORM_BLOCK,
	BC1_RGBA_SRGB_BLOCK,
	BC2_UNORM_BLOCK,
	BC2_SRGB_BLOCK,
	BC3_UNORM_BLOCK,
	BC3_SRGB_BLOCK,
	BC4_UNORM_BLOCK,
	BC4_SNORM_BLOCK,
	BC5_UNORM_BLOCK,
	BC5_SNORM_BLOCK,
	BC6H_UFLOAT_BLOCK,
	BC6H_SFLOAT_BLOCK,
	BC7_UNORM_BLOCK,
	BC7_SRGB_BLOCK,

	ETC1_R8G8B8_UNORM_BLOCK,
	ETC2_R8G8B8_UNORM_BLOCK,
	ETC2_R8G8B8_SRGB_BLOCK,
	ETC2_R8G8B8A1_UNORM_BLOCK,
	ETC2_R8G8B8A1_SRGB_BLOCK,
	ETC2_R8G8B8A8_UNORM_BLOCK,
	ETC2_R8G8B8A8_SRGB_BLOCK,
	EAC_R11_UNORM_BLOCK,
	EAC_R11_SNORM_BLOCK,
	EAC_R11G11_UNORM_BLOCK,
	EAC_R11G11_SNORM_BLOCK,

	ASTC_4x4_UNORM_BLOCK,
	ASTC_4x4_SRGB_BLOCK,
	ASTC_5x4_UNORM_BLOCK,
	ASTC_5x4_SRGB_BLOCK,
	ASTC_5x5_UNORM_BLOCK,
	ASTC_5x5_SRGB_BLOCK,
	ASTC_6x5_UNORM_BLOCK,
	ASTC_6x5_SRGB_BLOCK,
	ASTC_6x6_UNORM_BLOCK,
	ASTC_6x6_SRGB_BLOCK,
	ASTC_8x5_UNORM_BLOCK,
	ASTC_8x5_SRGB_BLOCK,
	ASTC_8x6_UNORM_BLOCK,
	ASTC_8x6_SRGB_BLOCK,
	ASTC_8x8_UNORM_BLOCK,
	ASTC_8x8_SRGB_BLOCK,
	ASTC_10x5_UNORM_BLOCK,
	ASTC_10x5_SRGB_BLOCK,
	ASTC_10x6_UNORM_BLOCK,
	ASTC_10x6_SRGB_BLOCK,
	ASTC_10x8_UNORM_BLOCK,
	ASTC_10x8_SRGB_BLOCK,
	ASTC_10x10_UNORM_BLOCK,
	ASTC_10x10_SRGB_BLOCK,
	ASTC_12x10_UNORM_BLOCK,
	ASTC_12x10_SRGB_BLOCK,
	ASTC_12x12_UNORM_BLOCK,
	ASTC_12x12_SRGB_BLOCK,
	UNDEFINED,
	NUM_FORMAT_TYPE = UNDEFINED,
};

struct RasterizationStateDesc
{
	bool        depthClampEnable;
	bool        rasterizerDiscardEnable;
	PolygonMode polygonMode;
	CullMode    cullMode;
	FrontFace   frontFace;
	bool        depthBiasEnable;
	float       depthBiasConstantFactor;
	float       depthBiasClamp;
	float       depthBiasSlopeFactor;
	float       lineWidth;
};

struct MultisampleStateDesc
{
	SampleCount rasterizationSamples;
	bool        sampleShadingEnable;
	float       minSampleShading;
	uint32_t    sampleMask;
	bool        alphaToCoverageEnable;
	bool        alphaToOneEnable;
};

struct DepthStencilStateDesc
{
	bool      depthTestEnable;
	bool      depthWriteEnable;
	CompareOp depthCompareOp;
	bool      depthBoundsTestEnable;
	bool      stencilTestEnable;
	StencilOp front;
	StencilOp back;
	float     minDepthBounds;
	float     maxDepthBounds;
};

struct ColorBlendAttachmentStateDesc
{
	bool           blendEnable;
	BlendFactor    srcColorBlendFactor;
	BlendFactor    dstColorBlendFactor;
	BlendOp        colorBlendOp;
	BlendFactor    srcAlphaBlendFactor;
	BlendFactor    dstAlphaBlendFactor;
	BlendOp        alphaBlendOp;
	ColorComponent colorWriteMask;
};

struct ColorBlendStateDesc
{
	bool                                 logicOpEnable;
	LogicOp                              logicOp;
	uint32_t                             attachmentCount;
	const ColorBlendAttachmentStateDesc* pAttachments;
	float                                blendConstants[4];
};

class Instance;
class Device;
class SwapChain;
class ImmediateContext;
class DeferredContext;

Result CreateInstance(Instance*& outInstance);
void DestroyInstance(Instance* instance);

} // namespace GLOV
