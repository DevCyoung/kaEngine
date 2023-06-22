#pragma once

namespace engine
{
	enum class eResMesh
	{
		dummy,
		End
	};

	const wchar_t* EnumResourcePath(eResMesh type);
}//namespace engine End
