#include "pch.h"
#include "EnumResourceTypeAnimation.h"

const wchar_t* eResAnimationPath[static_cast<UINT>(eResAnimation::End)]
{
	L"\\Animation\\Player\\DOWN.anim",
	L"\\Animation\\Player\\DOWN_READY.anim",
	L"\\Animation\\ATTACK_1.anim",
	L"\\Animation\\ATTACK_2.anim",
};

const wchar_t* EnumResourcePath(eResAnimation type)
{
	return eResAnimationPath[static_cast<UINT>(type)];
}

