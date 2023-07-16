#pragma once
#define PI 3.1415926535897f
#define Deg2Rad(degree) (degree * (PI / 180.0f))
#define Rad2Deg(radian) (radian * (180.0f / PI))
#include <random>

class Camera;

namespace helper
{	
	Vector2 RenderTargetToWorldUI(const Vector2& renderTargetMousePos, const Vector2& renderTargetSize);
	Vector3 ScreenMouseToWorld3D(const Vector3& screenMousePos, const Vector2& screenSize, 
		const Camera* const camera);
	Vector3 WindowScreenMouseToWorld3D(const Camera* const camera);

	XMINT2 GridIndex(const Vector3& selectWorldPos,
		const Vector2& cellSize, const XMUINT2& tileCountXY);
	Vector3 GridIndexToWorldPosition(const XMINT2& gridIndex, 
		const Vector2& cellSize, const XMUINT2& tileCountXY);
	bool IsInGrid(const XMINT2& gridIndex, const XMUINT2& tileCountXY);
}

namespace helper::math
{
	void INT2MinAndMax(const XMINT2& a, const XMINT2& b, XMINT2* const outMin, XMINT2* const outMax);
	float LerpCosBtwZeroAndOne(const float x);
	float LerpSinBtwZeroAndOne(const float x);
}

namespace helper::rand
{
	int RandInt(int a, int b);
}