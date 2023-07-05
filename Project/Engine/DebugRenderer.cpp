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
	tDebugDrawInfo drawInfo =
	{
		WORLD_POS,
		Vector3(0.f, 0.f, 0.f),
		Vector3(RECT_Scale.x, RECT_Scale.y, 1.f),
		DRAW_TIME
	};

	mDebugDrawInfos.push_back(drawInfo);
}

void DebugRenderer::Render(const Camera* const P_CAMERA)
{
	const Mesh* const P_MESH = gResourceManager->FindOrNull<Mesh>(L"Rect");
	const Shader* const P_SHADER = gResourceManager->FindOrNull<Shader>(L"Debug");

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

		gGraphicDevice->BindMesh(P_MESH);
		gGraphicDevice->BindIA(P_SHADER);
		gGraphicDevice->BindPS(P_SHADER);
		gGraphicDevice->BindVS(P_SHADER);

		gGraphicDevice->BindBS(eBSType::Default);
		gGraphicDevice->BindDS(eDSType::None);
		gGraphicDevice->BindRS(eRSType::WireframeNone);

		gGraphicDevice->Draw(P_MESH);

		drawInfo.drawTime -= gDeltaTime;
	}

	mDebugDrawInfos.erase(std::remove_if(mDebugDrawInfos.begin(), mDebugDrawInfos.end(),
		[](tDebugDrawInfo& drawInfo) {return drawInfo.drawTime < 0.f; }), mDebugDrawInfos.end());
}
