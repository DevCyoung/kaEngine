#include "pch.h"
#include "EnumResourceTypeShader.h"

namespace engine
{
	const wchar_t* eResShaderPath[static_cast<UINT>(eResShader::End)]
	{
		L"\\Shader\\Header\\ConstantBuffer.fx",
		L"\\Shader\\Header\\Sampler.fx",
		L"\\Shader\\Header\\Struct.fx",
		L"\\Shader\\Header\\Texture.fx",
		L"\\Shader\\PixelShader.fx",
		L"\\Shader\\VertexShader.fx",
	};

	const wchar_t* EnumResourcePath(eResShader type)
	{
		return eResShaderPath[static_cast<UINT>(type)];
	}
}
