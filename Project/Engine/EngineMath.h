#pragma once
#define PI 3.1415926535897f
#define Deg2Rad(degree) (degree * (PI / 180.0f))
#define Rad2Deg(radian) (radian * (180.0f / PI))

class Camera;

namespace helper
{	
	Vector2 RenderTargetToWorldUI(const Vector2& RENDER_TARGET_POS, const Vector2& RENDER_TARGET_SIZE);

	Vector3 ScreenMouseToWorld3D(const Vector3& SCREEN_MOUSE_POS, const Vector2& SCREEN_SIZE, const Camera* const P_CAMERA);
	Vector3 WindowScreenMouseToWorld3D(const Camera* const P_CAMERA);

	float LerpCosBtwZeroAndOne(const float VALUE);
	float LerpSinBtwZeroAndOne(const float VALUE);
}
