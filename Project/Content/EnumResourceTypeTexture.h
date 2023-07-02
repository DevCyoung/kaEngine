#pragma once

enum class eResTexture
{
	charactor_atlas_zero_black,
	charactor_atlas_zero_ori,
	charactor_atlas_zero_s,
	charactor_atlas_zero_virus,
	UI_spr_cursor,
	UI_spr_hud,
	UI_spr_hud_battery,
	UI_spr_hud_subweapon,
	UI_spr_hud_timer_0,
	UI_spr_hud_timer_1,
	UI_spr_itemicons_0,
	UI_spr_katanaicons_0,
	UI_spr_keyboard_shift_0,
	UI_spr_keyboard_shift_1,
	UI_spr_left_click_1,
	UI_spr_right_click_1,
	UI_spr_timer,
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

