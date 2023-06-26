#pragma once

enum class eResTexture
{
	charactor_atlas_zero_black,
	charactor_atlas_zero_ori,
	charactor_atlas_zero_s,
	charactor_atlas_zero_virus,
	bg_bar_0,
	bg_cathedral_background_0,
	bg_club_full_0,
	bg_dreamshed_0,
	bg_studio_outside_0,
	door,
	orange,
	spr_bg_neighbor_apartment_0,
	TILE,
	walk,
	End
};

const wchar_t* EnumResourcePath(eResTexture type);

