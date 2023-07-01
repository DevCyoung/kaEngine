#include "pch.h"
#include "EngineMath.h"

namespace helper
{
	Vector2 ScreenToUIPostion(const Vector2& screenPos, const Vector2& screenSize)
	{		
		return Vector2(screenPos.x - screenSize.x / 2, -screenPos.y + screenSize.y / 2);	
	}
}
