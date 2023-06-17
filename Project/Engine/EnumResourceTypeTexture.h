#pragma once

namespace engine
{
	enum class eResTexture
	{
		Fighter,
		End
	};

	const wchar_t* EnumResourcePath(eResTexture type);
}
