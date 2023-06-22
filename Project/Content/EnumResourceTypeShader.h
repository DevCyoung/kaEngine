#pragma once

namespace engine
{
	enum class eResShader
	{
		Header_ConstantBuffer,
		Header_Sampler,
		Header_Struct,
		Header_Texture,
		PixelShader,
		VertexShader,
		End
	};

	const wchar_t* EnumResourcePath(eResShader type);
}//namespace engine End
