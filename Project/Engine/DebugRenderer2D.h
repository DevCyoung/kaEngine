#pragma once
#include <d3d11.h>

class GameObject;
class Camera;
class Shader;

class DebugRenderer2D
{
public:
	friend class RenderTargetRenderer;
private:
	DebugRenderer2D();
	virtual ~DebugRenderer2D();

public:
	void DrawFillRect2D(const Vector3& WORLD_POS, const Vector2& RECT_SCALE, 
		const float DRAW_TIME, const Vector4& FILL_COLOR);
	void DrawFillRect2D2(const Vector3& WORLD_LEFT_UP_POS, const Vector3& WORLD_RIGHT_BOTTOM_POS, 
		const float DRAW_TIME, const Vector4& FILL_COLOR);
	void DrawGrid2D(const Vector3& WORLD_POS, const Vector2& TILE_SIZE, const Vector2& TILE_COUNT, 
		const float DRAW_TIME, const Vector4& FILL_COLOR);

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
		Vector3 Scale;
		Vector3 Rotation;
		Vector3 MousePos;
		Vector2 XYCount;

		Vector4 FillColor;
		Vector4 OutLineColor;

		float DrawTime;
	};

	void renderRect2D(const tDebugDrawInfo& DEBUG_DRAW_INFO);
	void renderGrid2D(const tDebugDrawInfo& DEBUG_DRAW_INFO);
	void render(const Camera* const P_MAIN_CAMERA);
private:	
	Shader* mDebugDrawShader[static_cast<UINT>(eDebugDrawType::End)];
	std::vector<tDebugDrawInfo> mDebugDrawInfos;
};


