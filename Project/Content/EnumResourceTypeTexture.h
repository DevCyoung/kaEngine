#pragma once

enum class eResTexture
{
	charactor_atlas,
	charactor_atlas_zero_black,
	charactor_atlas_zero_ori,
	charactor_atlas_zero_s,
	charactor_atlas_zero_virus,
	door,
	orange,
	TILE,
	walk,
	End
};

const wchar_t* EnumResourcePath(eResTexture type);
//namespace engine End