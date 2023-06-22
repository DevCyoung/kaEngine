#include "pch.h"
#include "EnumResourceTypeFont.h"

namespace engine
{
	const wchar_t* eResFontPath[static_cast<UINT>(eResFont::End)]
	{
		L"\\Font\\dummy.font",
	};

	const wchar_t* EnumResourcePath(eResFont type)
	{
		return eResFontPath[static_cast<UINT>(type)];
	}
}//namespace engine End
