#include "pch.h"
#include "EnumResourceTypeShader.h"

const wchar_t* eResShaderPath[static_cast<UINT>(eResShader::End)]
{
	L"\\Shader\\Header\\ConstantBuffer.fxh",
	L"\\Shader\\Header\\Sampler.fxh",
	L"\\Shader\\Header\\Struct.fxh",
	L"\\Shader\\Header\\TestShaderHeader.fxh",
	L"\\Shader\\Header\\Texture.fxh",
	L"\\Shader\\PSDebug.hlsl",
	L"\\Shader\\PSGrid.hlsl",
	L"\\Shader\\PSSprite.hlsl",
	L"\\Shader\\VSDebug.hlsl",
	L"\\Shader\\VSSprite.hlsl",
};

const wchar_t* EnumResourcePath(eResShader type)
{
	return eResShaderPath[static_cast<UINT>(type)];
}

