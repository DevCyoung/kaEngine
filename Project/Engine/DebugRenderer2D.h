#pragma once
#include <d3d11.h>

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
	void DrawFillRect2D(const Vector3& worldPos, const Vector2& rectScale,
		const float drawTime, const Vector4& fillColor);

	void DrawFillRect2D2(const Vector3& wolrdLeftUpPos, const Vector3& worldRightDownPos, 
		const float drawTime, const Vector4& fillColor);

	void DrawGrid2D(const Vector3& worldPos, 
		const Vector2& cellSizeXY, const tUINT2& tileCountXY,
		const float drawTime, const Vector4& fillColor);

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
		Vector4 FillColor;
		Vector4 OutLineColor;
		tUINT2 XYCount;
		float DrawTime;
	};

	void renderRect2D(const tDebugDrawInfo& debugDrawInfo);
	void renderGrid2D(const tDebugDrawInfo& debugDrawInfo);
	void render(const Camera* const camera);

private:	
	Shader* mDebugDrawShader[static_cast<UINT>(eDebugDrawType::End)];
	std::vector<tDebugDrawInfo> mDebugDrawInfos;
};


