#pragma once
#include <d3d11.h>

class GameObject;
class Camera;

class DebugRenderer2D
{
public:
	DebugRenderer2D();
	virtual ~DebugRenderer2D();

	void DrawWorld2DRect(const Vector3& WORLD_POS, const Vector2& RECT_SCALE, const float DRAW_TIME);
	void DrawGrid2D(const Vector3& WORLD_POS, const Vector2& TILE_SIZE, const Vector2& TILE_COUNT, const float DRAW_TIME);

	void Render(const Camera* const P_MAIN_CAMERA);

private:
	enum class eDebugDrawType
	{
		Grid2D,
		Rect2D,
		End,
	};

	struct tDebugDrawInfo
	{
		eDebugDrawType DebugDrawType;
		Vector3 WorldPos;
		Vector3 Rotation;
		Vector3 Scale;
		Vector3 MousePos;
		Vector2 XYCount;
		float DrawTime;
	};

	void renderRect2D();
	void renderGrid2D(const tDebugDrawInfo& drawInfo);

private:
	GameObject* mDebugDrawRectObject;
	std::vector<tDebugDrawInfo> mDebugDrawInfos;
};


