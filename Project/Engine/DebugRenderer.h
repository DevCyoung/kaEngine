#pragma once
#include <d3d11.h>

class GameObject;
class Camera;

class DebugRenderer
{
public:
	DebugRenderer();
	virtual ~DebugRenderer();

	struct tDebugDrawInfo	
	{
		Vector3 worldPos;
		Vector3 rotation;
		Vector3 rectScale;
		float drawTime;
	};

	void DrawWorld2DRect(const Vector3& WORLD_POS, const Vector2& RECT_Scale, const float DRAW_TIME);

	void Render(const Camera* const P_CAMERA);

private:
	GameObject* mDebugDrawRectObject;
	std::vector<tDebugDrawInfo> mDebugDrawInfos;

};

