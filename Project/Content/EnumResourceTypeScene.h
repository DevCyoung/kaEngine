#pragma once

namespace engine
{
	enum class eResScene
	{
		PixelSample,
		End
	};

	const wchar_t* EnumResourcePath(eResScene type);
}
