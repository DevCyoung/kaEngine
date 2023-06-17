#include "pch.h"
#include "EnumResourceTypeShader.h"

namespace engine
{
	const wchar_t* eResShaderPath[static_cast<UINT>(eResShader::End)]
	{
		L"\\Shader\\Default\\PixelShader.hlsl",
		L"\\Shader\\Default\\VertexShader.hlsl",
	};

	const wchar_t* EnumResourcePath(eResShader type)
	{
		return eResShaderPath[static_cast<UINT>(type)];
	}
}
