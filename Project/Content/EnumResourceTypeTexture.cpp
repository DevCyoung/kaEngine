#include "pch.h"
#include "EnumResourceTypeTexture.h"

static constexpr const wchar_t* eResTexturePath[static_cast<UINT>(eResTexture::End)]
{
	L"\\Texture\\charactor\\atlas_zero_black.bmp",
	L"\\Texture\\charactor\\atlas_zero_ori.bmp",
	L"\\Texture\\charactor\\atlas_zero_s.bmp",
	L"\\Texture\\charactor\\atlas_zero_virus.bmp",
	L"\\Texture\\TileMap\\bg_club_background.png",
	L"\\Texture\\TileMap\\bg_haunted_background.png",
	L"\\Texture\\UI\\spr_cursor.png",
	L"\\Texture\\UI\\spr_hud.png",
	L"\\Texture\\UI\\spr_hud_battery.png",
	L"\\Texture\\UI\\spr_hud_subweapon.png",
	L"\\Texture\\UI\\spr_hud_timer_0.png",
	L"\\Texture\\UI\\spr_hud_timer_1.png",
	L"\\Texture\\UI\\spr_itemicons_0.png",
	L"\\Texture\\UI\\spr_katanaicons_0.png",
	L"\\Texture\\UI\\spr_keyboard_shift_0.png",
	L"\\Texture\\UI\\spr_keyboard_shift_1.png",
	L"\\Texture\\UI\\spr_left_click_1.png",
	L"\\Texture\\UI\\spr_right_click_1.png",
	L"\\Texture\\UI\\spr_timer.png",
	L"\\Texture\\bg_bar_0.png",
	L"\\Texture\\bg_cathedral_background_0.png",
	L"\\Texture\\bg_club_full_0.png",
	L"\\Texture\\bg_dreamshed_0.png",
	L"\\Texture\\bg_studio_outside_0.png",
	L"\\Texture\\door.bmp",
	L"\\Texture\\orange.bmp",
	L"\\Texture\\spr_bg_neighbor_apartment_0.png",
	L"\\Texture\\TILE.bmp",
	L"\\Texture\\walk.bmp",
};

const wchar_t* EnumResourcePath(eResTexture type)
{
	return eResTexturePath[static_cast<UINT>(type)];
}

