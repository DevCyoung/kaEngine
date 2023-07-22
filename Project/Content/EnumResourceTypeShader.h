#pragma once

enum class eResShader
{
	Header_ConstantBuffer,
	Header_Sampler,
	Header_Struct,
	Header_TestShaderHeader,
	Header_Texture,
	PSAnimation2D,
	PSFillDebug2D,
	PSGrid2D,
	PSLineDebug2D,
	PSSprite,
	VSFillDebug2D,
	VSGrid2D,
	VSLineDebug2D,
	VSSprite,
	End
};

const wchar_t* EnumResourcePath(eResShader type);

