#pragma once
#define PI 3.1415926535897f
#define Deg2Rad(degree) (degree * (PI / 180.0f))
#define Rad2Deg(radian) (radian * (180.0f / PI))

class Camera;

namespace helper
{	
	Vector2 RenderTargetToWorldUI(const Vector2& renderTargetMousePos, const Vector2& renderTargetSize);
	Vector3 ScreenMouseToWorld3D(const Vector3& screenMousePos, const Vector2& screenSize, 
		const Camera* const camera);
	Vector3 WindowScreenMouseToWorld3D(const Camera* const camera);

	tINT2 GridIndex(const Vector3& selectWorldPos,
		const Vector2& cellSize, const tUINT2& tileCountXY);
	Vector3 GridIndexToWorldPosition(const tINT2& gridIndex, 
		const Vector2& cellSize, const tUINT2& tileCountXY);
	bool IsInGrid(const tINT2& gridIndex, const tUINT2& tileCountXY);
}

namespace helper::math
{
	void INT2MinAndMax(const tINT2& a, const tINT2& b, tINT2* const outMin, tINT2* const outMax);
	float LerpCosBtwZeroAndOne(const float x);
	float LerpSinBtwZeroAndOne(const float x);
}