#pragma once
#define PI 3.1415926535897f
#define Deg2Rad(degree) (degree * (PI / 180.0f))
#define Rad2Deg(radian) (radian * (180.0f / PI))

namespace helper
{	
	Vector2 ScreenToWorldScreen(const Vector2& screenPos, 
		const Vector2& screenSize);

	//2D Camera
	Vector2 ScreenToWorld2D(const Vector2& screenPos, 
		const Vector2& screenSize, 
		const Vector3& cameraPos,
		const float cameraSize);

	float LerpCosBtwZeroAndOne(float value);
	float LerpSinBtwZeroAndOne(float value);
}
