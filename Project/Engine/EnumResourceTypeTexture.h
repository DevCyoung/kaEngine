#pragma once

namespace engine
{
	enum class eResTexture
	{
		OakUI,
		Ori,
		End
	};

	const wchar_t* EnumResourcePath(eResTexture type);
}
