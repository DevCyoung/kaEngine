#include "pch.h"
#include "EnumResourceTypeTexture.h"

namespace engine
{
	const wchar_t* eResTexturePath[static_cast<UINT>(eResTexture::End)]
	{
		L"\\Texture\\charactor\\atlas.bmp",
		L"\\Texture\\charactor\\atlas_zero_black.bmp",
		L"\\Texture\\charactor\\atlas_zero_ori.bmp",
		L"\\Texture\\charactor\\atlas_zero_s.bmp",
		L"\\Texture\\charactor\\atlas_zero_virus.bmp",
		L"\\Texture\\door.bmp",
		L"\\Texture\\orange.bmp",
		L"\\Texture\\TILE.bmp",
		L"\\Texture\\walk.bmp",
	};

	const wchar_t* EnumResourcePath(eResTexture type)
	{
		return eResTexturePath[static_cast<UINT>(type)];
	}
}//namespace engine End
