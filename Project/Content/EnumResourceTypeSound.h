#pragma once

namespace engine
{
	enum class eResSound
	{
		Die,
		End
	};

	const wchar_t* EnumResourcePath(eResSound type);
}//namespace engine End
