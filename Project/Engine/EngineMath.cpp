#include "pch.h"
#include "EngineMath.h"

/*
* 게임 에서 사용하는 UI 좌표계는 윈도우 좌표계와 동일하게 사용합니다.
* 윈도우 좌표계는 왼쪽 상단이 (0, 0)이고 오른쪽 하단이 (width, height)입니다.
*/

namespace helper
{
	Vector2 WindowScreenToUIPostion(const Vector2& screenPos, const Vector2& screenSize)
	{
		return Vector2(screenPos.x - screenSize.x / 2, -screenPos.y + screenSize.y / 2);
	}
}
