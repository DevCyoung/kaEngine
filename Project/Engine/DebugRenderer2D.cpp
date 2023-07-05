#include "pch.h"
#include "DebugRenderer2D.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "CBCollection.h"
#include "StructConstantBuffer.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "EngineMath.h"

DebugRenderer2D::DebugRenderer2D()
	: mDebugDrawRectObject(nullptr)
{
}

DebugRenderer2D::~DebugRenderer2D()
{
}

void DebugRenderer2D::DrawWorld2DRect(const Vector3& WORLD_POS,
	const Vector2& RECT_SCALE,
	const float DRAW_TIME)
{
	tDebugDrawInfo drawInfo = {};

	drawInfo.DebugDrawType = eDebugDrawType::Rect2D;
	drawInfo.WorldPos = WORLD_POS;
	drawInfo.Scale = Vector3(RECT_SCALE.x, RECT_SCALE.y, 1.f);
	drawInfo.DrawTime = DRAW_TIME;

	mDebugDrawInfos.push_back(drawInfo);
}


void DebugRenderer2D::DrawGrid2D(const Vector3& WORLD_POS,
	const Vector2& TILE_SIZE,
	const Vector2& TILE_COUNT,
	const float DRAW_TIME)
{
	tDebugDrawInfo drawInfo = {};

	drawInfo.DebugDrawType = eDebugDrawType::Grid2D;
	drawInfo.WorldPos = WORLD_POS;
	drawInfo.Scale = Vector3(TILE_SIZE.x * TILE_COUNT.x, TILE_SIZE.y * TILE_COUNT.y, 1.f);
	drawInfo.Rotation = Vector3::Zero;
	drawInfo.DrawTime = DRAW_TIME;
	drawInfo.XYCount = TILE_COUNT;

	mDebugDrawInfos.push_back(drawInfo);
}



void DebugRenderer2D::Render(const Camera* const P_MAIN_CAMERA)
{
	Assert(P_MAIN_CAMERA, WCHAR_IS_NULLPTR);

	tCBTransform tTrans = {};
	tTrans.View = P_MAIN_CAMERA->GetView();
	tTrans.Proj = P_MAIN_CAMERA->GetProjection();

	const Mesh* const P_MESH = gResourceManager->FindOrNull<Mesh>(L"Rect");
	gGraphicDevice->BindMesh(P_MESH);

	for (tDebugDrawInfo& drawInfo : mDebugDrawInfos)
	{		
		tTrans.World = Transform::CreateWorldMatrix(drawInfo.WorldPos, drawInfo.Rotation, drawInfo.Scale);
		gGraphicDevice->PassCB(eCBType::Transform, sizeof(tTrans), &tTrans);
		gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);

		Vector3 worldMousePos = helper::WindowScreenMouseToWorld3D(P_MAIN_CAMERA);

		//월드 좌표계의 Y는 그리드 좌표계와 반대이다.
		worldMousePos = Vector3(worldMousePos.x, -worldMousePos.y, worldMousePos.z);

		Shader* shader = nullptr;

		switch (drawInfo.DebugDrawType)
		{
		case eDebugDrawType::Rect2D:
			shader = gResourceManager->FindOrNull<Shader>(L"Debug");

			renderRect2D();
			break;
		case eDebugDrawType::Grid2D:
			shader = gResourceManager->FindOrNull<Shader>(L"DebugGrid");

			drawInfo.MousePos = worldMousePos + Vector3(drawInfo.Scale) / 2.f;
			renderGrid2D(drawInfo);
			break;
		default:
			Assert(P_MAIN_CAMERA, WCHAR_IS_INVALID_TYPE);
			break;
		}

		gGraphicDevice->BindIA(shader);
		gGraphicDevice->BindPS(shader);
		gGraphicDevice->BindVS(shader);

		gGraphicDevice->Draw(P_MESH);

		drawInfo.DrawTime -= gDeltaTime;
	}

	mDebugDrawInfos.erase(std::remove_if(mDebugDrawInfos.begin(), mDebugDrawInfos.end(),
		[](tDebugDrawInfo& drawInfo) {return drawInfo.DrawTime < 0.f; }), mDebugDrawInfos.end());
}

void DebugRenderer2D::renderRect2D()
{
	gGraphicDevice->BindRS(eRSType::CullNone);
	gGraphicDevice->BindBS(eBSType::AlphaBlend);
	gGraphicDevice->BindDS(eDSType::None);
}

void DebugRenderer2D::renderGrid2D(const tDebugDrawInfo& drawInfo)
{		
	tCBGridInfo tGrid = {};
	{
		tGrid.MouseWorldPos = drawInfo.MousePos;
		tGrid.Scale = Vector2(drawInfo.Scale.x, drawInfo.Scale.y);
		tGrid.XYCount[0] = static_cast<int>(drawInfo.XYCount.x);
		tGrid.XYCount[1] = static_cast<int>(drawInfo.XYCount.y);

		gGraphicDevice->PassCB(eCBType::GridInfo, sizeof(tGrid), &tGrid);
		gGraphicDevice->BindCB(eCBType::GridInfo, eShaderBindType::PS);
	}

	gGraphicDevice->BindRS(eRSType::CullNone);
	gGraphicDevice->BindBS(eBSType::Default);
	gGraphicDevice->BindDS(eDSType::None);	
}
