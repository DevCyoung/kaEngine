#pragma once

namespace engine
{
	enum class eResScene
	{
		dummy,
		End
	};

	const wchar_t* EnumResourcePath(eResScene type);
}//namespace engine End
