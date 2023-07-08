#pragma once
#define PI 3.1415926535897f
#define Deg2Rad(degree) (degree * (PI / 180.0f))
#define Rad2Deg(radian) (radian * (180.0f / PI))

class Camera;

namespace helper
{	
	Vector2 RenderTargetToWorldUI(const Vector2& renderTargetMousePos, const Vector2& renderTargetSize);
	Vector3 ScreenMouseToWorld3D(const Vector3& screenMousePos, const Vector2& screenSize, const Camera* const camera);
	Vector3 WindowScreenMouseToWorld3D(const Camera* const camera);

	float LerpCosBtwZeroAndOne(const float x);
	float LerpSinBtwZeroAndOne(const float x);
}
