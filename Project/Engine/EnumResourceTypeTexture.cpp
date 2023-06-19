#include "pch.h"
#include "EnumResourceTypeTexture.h"

namespace engine
{
	const wchar_t* eResTexturePath[static_cast<UINT>(eResTexture::End)]
	{
		L"\\Texture\\OakUI.bmp",
		L"\\Texture\\Ori.bmp",
	};

	const wchar_t* EnumResourcePath(eResTexture type)
	{
		return eResTexturePath[static_cast<UINT>(type)];
	}
}
