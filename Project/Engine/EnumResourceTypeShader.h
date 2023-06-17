#pragma once

namespace engine
{
	enum class eResShader
	{
		Default_PixelShader,
		Default_VertexShader,
		End
	};

	const wchar_t* EnumResourcePath(eResShader type);
}
