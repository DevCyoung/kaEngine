#include "pch.h"
#include "EnumResourceTypeScene.h"

namespace engine
{
	const wchar_t* eResScenePath[static_cast<UINT>(eResScene::End)]
	{
		L"\\Scene\\dummy.scene",
	};

	const wchar_t* EnumResourcePath(eResScene type)
	{
		return eResScenePath[static_cast<UINT>(type)];
	}
}//namespace engine End
