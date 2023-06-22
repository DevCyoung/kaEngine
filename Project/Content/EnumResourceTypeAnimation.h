#pragma once

namespace engine
{
	enum class eResAnimation
	{
		Player_DOWN,
		Player_DOWN_FINISH,
		Player_DOWN_READY,
		ATTACK_1,
		ATTACK_2,
		ATTACK_3,
		End
	};

	const wchar_t* EnumResourcePath(eResAnimation type);
}//namespace engine End
