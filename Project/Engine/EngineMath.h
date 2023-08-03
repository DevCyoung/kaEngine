#pragma once
#define PI 3.1415926535897f
#define Deg2Rad(degree) (degree * (PI / 180.0f))
#define Rad2Deg(radian) (radian * (180.0f / PI))
#define Deg2Vec2Dir(degree) Vector2(cosf(Deg2Rad(degree)), sinf(Deg2Rad(degree)))

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
	void Vector2MinAndMax(const Vector2& a, const Vector2& b, Vector2* const outMin, Vector2* const outMax);
	float LerpCosBtwZeroAndOne(const float x);
	float LerpSinBtwZeroAndOne(const float x);



#pragma region LineCollision
	bool LineAndLineCollision(const Vector3& s1, const Vector3& e1,
				const Vector3& s2, const Vector3& e2, Vector2* const outInter);

	bool LineAndLineCollision(const Vector2& s1, const Vector2& e1,
		const Vector2& s2, const Vector2& e2, Vector2* const outInter);

	bool _LineAndLineCollision(float x1, float y1, float x2, float y2,
		float x3, float y3, float x4, float y4, float* outInterX, float* outInterY);
#pragma endregion

	
}

namespace helper::rand
{
	int RandInt(int a, int b);
}