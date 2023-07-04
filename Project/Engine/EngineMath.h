#pragma once
#define PI 3.1415926535897f
#define Deg2Rad(degree) (degree * (PI / 180.0f))
#define Rad2Deg(radian) (radian * (180.0f / PI))

class Camera;

namespace helper
{	
	Vector2 ScreenToWorldScreen(const Vector2& RENDER_TARGET_MOUSE_POS,
		const Vector2& RENDER_TARGET_SIZE);

	//2D Camera
	Vector2 ScreenToWorld2D(const Vector2& RENDER_TARGET_MOUSE_POS,
		const Vector2& RENDER_TARGET_SIZE,
		const Vector3& CAMERA_POS,
		const float CAMERA_SIZE);

	Vector2 ScreenToWorld2D(const Vector2& RENDER_TARGET_MOUSE_POS,
		const Vector2& RENDER_TARGET_SIZE,
		const Camera* const P_CAMERA);

	Vector2 WindowScreenMouseToWorld2D(const Camera* const P_CAMERA);

	float LerpCosBtwZeroAndOne(const float VALUE);
	float LerpSinBtwZeroAndOne(const float VALUE);
}
