#include "pch.h"
#include "EnumResourceTypeShader.h"

static constexpr const wchar_t* eResShaderPath[static_cast<UINT>(eResShader::End)]
{
	L"\\Shader\\Header\\ConstantBuffer.fxh",
	L"\\Shader\\Header\\Sampler.fxh",
	L"\\Shader\\Header\\Struct.fxh",
	L"\\Shader\\Header\\TestShaderHeader.fxh",
	L"\\Shader\\Header\\Texture.fxh",
	L"\\Shader\\PSAnimation2D.hlsl",
	L"\\Shader\\PSFillDebug2D.hlsl",
	L"\\Shader\\PSGrid2D.hlsl",
	L"\\Shader\\PSLineDebug2D.hlsl",
	L"\\Shader\\PSSprite2D.hlsl",
	L"\\Shader\\PSUI2D.hlsl",
	L"\\Shader\\VSAnimation2D.hlsl",
	L"\\Shader\\VSFillDebug2D.hlsl",
	L"\\Shader\\VSGrid2D.hlsl",
	L"\\Shader\\VSLineDebug2D.hlsl",
	L"\\Shader\\VSSprite2D.hlsl",
	L"\\Shader\\VSUI2D.hlsl",
};

const wchar_t* EnumResourcePath(eResShader type)
{
	return eResShaderPath[static_cast<UINT>(type)];
}

