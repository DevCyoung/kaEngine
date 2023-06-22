#pragma once

namespace engine
{
	enum class eResFont
	{
		dummy,
		End
	};

	const wchar_t* EnumResourcePath(eResFont type);
}//namespace engine End
