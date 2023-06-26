#pragma once

enum class eResAnimation
{
	Player_DOWN,
	Player_DOWN_READY,
	ATTACK_1,
	ATTACK_2,
	End
};

const wchar_t* EnumResourcePath(eResAnimation type);

