#include "pch.h"
#include "EnumResourceTypeShader.h"

namespace engine
{
	const wchar_t* eResShaderPath[static_cast<UINT>(eResShader::End)]
	{
		L"\\Shader\\Header\\ConstantBuffer.fxh",
		L"\\Shader\\Header\\Sampler.fxh",
		L"\\Shader\\Header\\Struct.fxh",
		L"\\Shader\\Header\\Texture.fxh",
		L"\\Shader\\PixelShader.hlsl",
		L"\\Shader\\VertexShader.hlsl",
	};

	const wchar_t* EnumResourcePath(eResShader type)
	{
		return eResShaderPath[static_cast<UINT>(type)];
	}
}//namespace engine End
