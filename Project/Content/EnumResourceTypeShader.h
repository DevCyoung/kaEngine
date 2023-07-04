#pragma once

enum class eResShader
{
	Header_ConstantBuffer,
	Header_Sampler,
	Header_Struct,
	Header_TestShaderHeader,
	Header_Texture,
	PixelDebug,
	PixelShader,
	VertexShader,
	End
};

const wchar_t* EnumResourcePath(eResShader type);

