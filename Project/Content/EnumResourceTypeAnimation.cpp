#include "pch.h"
#include "EnumResourceTypeAnimation.h"

namespace engine
{
	const wchar_t* eResAnimationPath[static_cast<UINT>(eResAnimation::End)]
	{
		L"\\Animation\\Player\\DOWN.anim",
		L"\\Animation\\Player\\DOWN_FINISH.anim",
		L"\\Animation\\Player\\DOWN_READY.anim",
		L"\\Animation\\ATTACK_1.anim",
		L"\\Animation\\ATTACK_2.anim",
		L"\\Animation\\ATTACK_3.anim",
	};

	const wchar_t* EnumResourcePath(eResAnimation type)
	{
		return eResAnimationPath[static_cast<UINT>(type)];
	}
}//namespace engine End
