#include "pch.h"
#include "DebugRenderer.h"
#include "GameObject.h"
#include "DebugRenderer2D.h"

#include "DebugRenderer2D.h"
#include "Camera.h"
#include "Material.h"
#include "Textrue.h"
#include "Shader.h"
#include "CBCollection.h"
#include "StructConstantBuffer.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "Transform.h"

#include "ResourceManager.h"
#include "Mesh.h"
#include "Shader.h"

#include "TimeManager.h"


#include "InputManager.h"
#include "EngineMath.h"

DebugRenderer::DebugRenderer()
	: mDebugDrawRectObject(nullptr)
{
}

DebugRenderer::~DebugRenderer()
{
}

void DebugRenderer::DrawWorld2DRect(const Vector3& WORLD_POS,
	const Vector2& RECT_Scale,
	const float DRAW_TIME)
{
	tDebugDrawInfo drawInfo = {};

	drawInfo.type = eDebugDrawType::Rect2D;
	drawInfo.worldPos = WORLD_POS;
	drawInfo.rectScale = Vector3(RECT_Scale.x, RECT_Scale.y, 1.f);
	drawInfo.drawTime = DRAW_TIME;

	mDebugDrawInfos.push_back(drawInfo);
}

void DebugRenderer::DrawGrid2D(const Vector3& WORLD_POS, 
	const Vector2& XY_SIZE,
	const Vector2& XY_COUNT,
	const float DRAW_TIME)
{
	tDebugDrawInfo drawInfo = {};

	drawInfo.type = eDebugDrawType::Grid2D;
	drawInfo.worldPos = WORLD_POS;
	drawInfo.rectScale = Vector3(XY_SIZE.x * XY_COUNT.x, XY_SIZE.y * XY_COUNT.y, 1.f);
	drawInfo.drawTime = DRAW_TIME;
	drawInfo.xyCount = XY_COUNT;

	mDebugDrawInfos.push_back(drawInfo);
}



void DebugRenderer::Render(const Camera* const P_CAMERA)
{

	for (tDebugDrawInfo& drawInfo : mDebugDrawInfos)
	{
		tCBTransform tTrans = {};
		{
			tTrans.World = Transform::CreateWorldMatrix(drawInfo.worldPos, drawInfo.rotation, drawInfo.rectScale);
			tTrans.View = P_CAMERA->GetView();
			tTrans.Proj = P_CAMERA->GetProjection();
		}
		gGraphicDevice->PassCB(eCBType::Transform, sizeof(tTrans), &tTrans);
		gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);


		Vector3 mousePos = helper::WindowScreenMouseToWorld3D(P_CAMERA);

		mousePos = Vector3(mousePos.x, -mousePos.y, mousePos.z);


		switch (drawInfo.type)
		{
		case eDebugDrawType::Rect2D:
			renderRect2D();
			break;
		case eDebugDrawType::Grid2D:
			drawInfo.mousePos = mousePos + Vector3(drawInfo.rectScale) / 2.f;
			renderGrid2D(drawInfo);
			break;
		default:
			break;
		}

		drawInfo.drawTime -= gDeltaTime;
	}

	mDebugDrawInfos.erase(std::remove_if(mDebugDrawInfos.begin(), mDebugDrawInfos.end(),
		[](tDebugDrawInfo& drawInfo) {return drawInfo.drawTime < 0.f; }), mDebugDrawInfos.end());
}

void DebugRenderer::renderRect2D()
{
	const Mesh* const P_MESH = gResourceManager->FindOrNull<Mesh>(L"Rect");
	const Shader* const P_SHADER = gResourceManager->FindOrNull<Shader>(L"Debug");

	gGraphicDevice->BindMesh(P_MESH);
	gGraphicDevice->BindIA(P_SHADER);
	gGraphicDevice->BindPS(P_SHADER);
	gGraphicDevice->BindVS(P_SHADER);

	gGraphicDevice->BindRS(eRSType::CullNone);
	gGraphicDevice->BindBS(eBSType::AlphaBlend);
	gGraphicDevice->BindDS(eDSType::None);

	gGraphicDevice->Draw(P_MESH);
}

void DebugRenderer::renderGrid2D(const tDebugDrawInfo& drawInfo)
{
	const Mesh* const P_MESH = gResourceManager->FindOrNull<Mesh>(L"Rect");
	const Shader* const P_SHADER = gResourceManager->FindOrNull<Shader>(L"DebugGrid");

	tCBGridInfo tGrid = {};
	{
		tGrid.MouseWorldPos = drawInfo.mousePos;
		tGrid.Scale = Vector2(drawInfo.rectScale.x, drawInfo.rectScale.y);
		tGrid.XYCount[0] = static_cast<int>(drawInfo.xyCount.x);
		tGrid.XYCount[1] = static_cast<int>(drawInfo.xyCount.y);
	}

	gGraphicDevice->PassCB(eCBType::GridInfo, sizeof(tGrid), &tGrid);	
	gGraphicDevice->BindCB(eCBType::GridInfo, eShaderBindType::PS);

	gGraphicDevice->BindMesh(P_MESH);
	gGraphicDevice->BindIA(P_SHADER);
	gGraphicDevice->BindPS(P_SHADER);
	gGraphicDevice->BindVS(P_SHADER);

	gGraphicDevice->BindRS(eRSType::CullNone);
	gGraphicDevice->BindBS(eBSType::AlphaBlend);
	gGraphicDevice->BindDS(eDSType::None);

	gGraphicDevice->Draw(P_MESH);
}
