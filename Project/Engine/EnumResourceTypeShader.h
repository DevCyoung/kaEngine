#pragma once

namespace engine
{
	enum class eResShader
	{
		Default_PixelShader,
		Default_VertexShader,
		Sample_PixelSample,
		Sample_VertexSample,
		End
	};

	const wchar_t* EnumResourcePath(eResShader type);
}
