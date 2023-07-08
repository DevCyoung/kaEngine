#include "pch.h"
#include "DebugRenderer2D.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "CBCollection.h"
#include "StructConstantBuffer.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "ResourceManager.h"
#include "EngineMath.h"

DebugRenderer2D::DebugRenderer2D()
	: mDebugDrawShader{ 0, }
{
	mDebugDrawShader[static_cast<UINT>(eDebugDrawType::Rect2D)] = gResourceManager->FindOrNull<Shader>(L"DebugRect2D");
	mDebugDrawShader[static_cast<UINT>(eDebugDrawType::Grid2D)] = gResourceManager->FindOrNull<Shader>(L"DebugGrid2D");
}

DebugRenderer2D::~DebugRenderer2D()
{
}

void DebugRenderer2D::DrawFillRect2D(const Vector3& worldPos,
	const Vector2& rectScale,
	const float drawTime, const Vector4& fillColor)
{
	tDebugDrawInfo drawInfo = {};

	drawInfo.DebugDrawType = eDebugDrawType::Rect2D;
	drawInfo.WorldPos = worldPos;
	drawInfo.Scale = Vector3(rectScale.x, rectScale.y, 1.f);
	drawInfo.DrawTime = drawTime;
	drawInfo.FillColor = fillColor;

	mDebugDrawInfos.push_back(drawInfo);
}

void DebugRenderer2D::DrawFillRect2D2(const Vector3& WORLD_LEFT_UP_POS,
	const Vector3& WORLD_RIGHT_BOTTOM_POS,
	const float drawTime, const Vector4& fillColor)
{
	const Vector3 WORLD_POS = (WORLD_LEFT_UP_POS + WORLD_RIGHT_BOTTOM_POS) * 0.5f;
	const Vector3 RECT_SCALE_3D = WORLD_RIGHT_BOTTOM_POS - WORLD_LEFT_UP_POS;

	DrawFillRect2D(WORLD_POS, Vector2(RECT_SCALE_3D.x, RECT_SCALE_3D.y), drawTime, fillColor);
}


void DebugRenderer2D::DrawGrid2D(const Vector3& worldPos,
	const Vector2& cellSizeXY, const tUINT2& tileCountXY,
	const float drawTime, const Vector4& fillColor)
{
	tDebugDrawInfo drawInfo = {};

	drawInfo.DebugDrawType = eDebugDrawType::Grid2D;
	drawInfo.WorldPos = worldPos;
	drawInfo.Scale = Vector3(cellSizeXY.x * tileCountXY.x, cellSizeXY.y * tileCountXY.y, 1.f);
	drawInfo.Rotation = Vector3::Zero;
	drawInfo.DrawTime = drawTime;
	drawInfo.XYCount = tileCountXY;
	drawInfo.FillColor = fillColor;

	mDebugDrawInfos.push_back(drawInfo);
}

void DebugRenderer2D::render(const Camera* const camera)
{
	Assert(camera, WCHAR_IS_NULLPTR);

	if (mDebugDrawInfos.empty())
	{
		return;
	}

	tCBTransform CBTransform = {};

	CBTransform.View = camera->GetView();
	CBTransform.Proj = camera->GetProjection();

	const Mesh* const P_MESH = gResourceManager->FindOrNull<Mesh>(L"Rect");

	gGraphicDevice->BindMesh(P_MESH);

	for (tDebugDrawInfo& drawInfo : mDebugDrawInfos)
	{	
		const Shader* const P_SHADER = mDebugDrawShader[static_cast<UINT>(drawInfo.DebugDrawType)];		
		Vector3 worldMousePos = helper::WindowScreenMouseToWorld3D(camera);

		worldMousePos = Vector3(worldMousePos.x, -worldMousePos.y, worldMousePos.z);
		CBTransform.World = Transform::CreateWorldMatrix(drawInfo.WorldPos, drawInfo.Rotation, drawInfo.Scale);

		gGraphicDevice->PassCB(eCBType::Transform, sizeof(CBTransform), &CBTransform);
		gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);

		gGraphicDevice->BindIA(P_SHADER);
		gGraphicDevice->BindPS(P_SHADER);
		gGraphicDevice->BindVS(P_SHADER);

		gGraphicDevice->BindRS(P_SHADER->GetRSType());
		gGraphicDevice->BindBS(P_SHADER->GetBSType());
		gGraphicDevice->BindDS(P_SHADER->GetDSType());

		switch (drawInfo.DebugDrawType)
		{
		case eDebugDrawType::Rect2D:
			renderRect2D(drawInfo);
			break;

		case eDebugDrawType::Grid2D:
			drawInfo.MousePos = worldMousePos + Vector3(drawInfo.Scale) / 2.f;
			renderGrid2D(drawInfo);
			break;

		default:
			Assert(false, WCHAR_IS_INVALID_TYPE);
			break;
		}

		gGraphicDevice->Draw(P_MESH);

		drawInfo.DrawTime -= gDeltaTime;
	}

	mDebugDrawInfos.erase(std::remove_if(mDebugDrawInfos.begin(), mDebugDrawInfos.end(),
		[](tDebugDrawInfo& drawInfo) { return drawInfo.DrawTime <= 0.f; }), mDebugDrawInfos.end());
}

void DebugRenderer2D::renderRect2D(const tDebugDrawInfo& drawInfo)
{
	tCBDebugInfo CBRectInfo = {};
	{
		CBRectInfo.Color_1 = drawInfo.FillColor;

		gGraphicDevice->PassCB(eCBType::DebugInfo, sizeof(CBRectInfo), &CBRectInfo);
		gGraphicDevice->BindCB(eCBType::DebugInfo, eShaderBindType::PS);
	}
}

void DebugRenderer2D::renderGrid2D(const tDebugDrawInfo& debugDrawInfo)
{
	tCBDebugInfo CBGridInfo = {};
	{
		CBGridInfo.MouseWorldPos = debugDrawInfo.MousePos;
		CBGridInfo.Scale = Vector2(debugDrawInfo.Scale.x, debugDrawInfo.Scale.y);
		CBGridInfo.XYCount[0] = static_cast<int>(debugDrawInfo.XYCount.x);
		CBGridInfo.XYCount[1] = static_cast<int>(debugDrawInfo.XYCount.y);

		CBGridInfo.Color_0 = debugDrawInfo.OutLineColor;
		CBGridInfo.Color_1 = debugDrawInfo.FillColor;

		gGraphicDevice->PassCB(eCBType::DebugInfo, sizeof(CBGridInfo), &CBGridInfo);
		gGraphicDevice->BindCB(eCBType::DebugInfo, eShaderBindType::PS);
	}
}
