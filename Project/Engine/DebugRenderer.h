#pragma once
#include <d3d11.h>

class GameObject;
class Camera;

class DebugRenderer
{
	enum class eDebugDrawType
	{
		Rect2D,
		Grid2D,
		End,
	};

public:
	DebugRenderer();
	virtual ~DebugRenderer();

	struct tDebugDrawInfo	
	{
		eDebugDrawType type;
		Vector3 worldPos;
		Vector3 mousePos;
		Vector3 rotation;
		Vector3 rectScale;
		Vector2 xyCount;
		float drawTime;
	};

	void DrawWorld2DRect(const Vector3& WORLD_POS, const Vector2& RECT_Scale, const float DRAW_TIME);
	void DrawGrid2D(const Vector3& WORLD_POS, const Vector2& XY_SIZE, const Vector2& XY_COUNT, const float DRAW_TIME);


	void Render(const Camera* const P_CAMERA);

	void renderRect2D();
	void renderGrid2D(const tDebugDrawInfo& drawInfo);

private:
	GameObject* mDebugDrawRectObject;
	std::vector<tDebugDrawInfo> mDebugDrawInfos;

};

