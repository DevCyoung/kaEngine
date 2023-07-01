#pragma once
#define PI 3.1415926535897f
#define Deg2Rad(degree) (degree * (PI / 180.0f))
#define Rad2Deg(radian) (radian * (180.0f / PI))

namespace helper
{
	Vector2 ScreenToUIPostion(const Vector2& screenPos, const Vector2& screenSize);
}
