#pragma once

namespace engine
{
	enum class eResTexture
	{
		TILE,
		walk,
		End
	};

	const wchar_t* EnumResourcePath(eResTexture type);
}
