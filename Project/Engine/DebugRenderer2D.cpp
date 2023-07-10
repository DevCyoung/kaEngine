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
	: mDebugMaterial{ 0, }
{
	{
		tDebugMaterial debugMaterial = {};
		debugMaterial.debugMesh = gResourceManager->FindOrNull<Mesh>(L"LineRect2D");
		debugMaterial.debugShader = gResourceManager->Find<Shader>(L"LineDebug2D");
		mDebugMaterial[static_cast<UINT>(eDebugDrawType::Rect2D)] = debugMaterial;
	}

	{
		tDebugMaterial debugMaterial = {};
		debugMaterial.debugMesh = gResourceManager->FindOrNull<Mesh>(L"FillRect2D");
		debugMaterial.debugShader = gResourceManager->Find<Shader>(L"FillDebug2D");
		mDebugMaterial[static_cast<UINT>(eDebugDrawType::FillRect2D)] = debugMaterial;
	}

	{
		tDebugMaterial debugMaterial = {};
		debugMaterial.debugMesh = gResourceManager->FindOrNull<Mesh>(L"LineCircle2D");
		debugMaterial.debugShader = gResourceManager->Find<Shader>(L"LineDebug2D");
		mDebugMaterial[static_cast<UINT>(eDebugDrawType::Circle2D)] = debugMaterial;
	}

	{
		tDebugMaterial debugMaterial = {};
		debugMaterial.debugMesh = gResourceManager->FindOrNull<Mesh>(L"FillCircle2D");
		debugMaterial.debugShader = gResourceManager->Find<Shader>(L"FillDebug2D");
		mDebugMaterial[static_cast<UINT>(eDebugDrawType::FillCircle2D)] = debugMaterial;
	}

	{
		tDebugMaterial debugMaterial = {};
		debugMaterial.debugMesh = gResourceManager->FindOrNull<Mesh>(L"Line");
		debugMaterial.debugShader = gResourceManager->Find<Shader>(L"LineDebug2D");
		mDebugMaterial[static_cast<UINT>(eDebugDrawType::Line2D)] = debugMaterial;
	}

	{
		tDebugMaterial debugMaterial = {};
		debugMaterial.debugMesh = gResourceManager->FindOrNull<Mesh>(L"FillRect2D");
		debugMaterial.debugShader = gResourceManager->Find<Shader>(L"DebugGrid2D");
		mDebugMaterial[static_cast<UINT>(eDebugDrawType::Grid2D)] = debugMaterial;
	}


}

DebugRenderer2D::~DebugRenderer2D()
{
}

void DebugRenderer2D::DrawRect2D(const Vector3& worldPos,
	const Vector2& rectScale,
	const float drawTime, const Vector4& outLineColor)
{
	tDebugDrawInfo drawInfo = {};

	drawInfo.DebugDrawType = eDebugDrawType::Rect2D;
	drawInfo.WorldPos = worldPos;
	drawInfo.Scale = Vector3(rectScale.x, rectScale.y, 1.f);
	drawInfo.Rotation = Vector3::Zero;
	drawInfo.DrawTime = drawTime;
	drawInfo.OutLineColor = outLineColor;

	mDebugDrawInfos.push_back(drawInfo);
}

void DebugRenderer2D::DrawRect2D2(const Vector3& wolrdLeftUpPos,
	const Vector3& worldRightDownPos,
	const float drawTime, const Vector4& outLineColor)
{
	const Vector3 WORLD_POS = (wolrdLeftUpPos + worldRightDownPos) * 0.5f;
	const Vector3 RECT_SCALE_3D = worldRightDownPos - wolrdLeftUpPos;

	DrawRect2D(WORLD_POS, Vector2(RECT_SCALE_3D.x, RECT_SCALE_3D.y), drawTime, outLineColor);
}

void DebugRenderer2D::DrawFillRect2D(const Vector3& worldPos,
	const Vector2& rectScale,
	const float drawTime, const Vector4& fillColor)
{
	tDebugDrawInfo drawInfo = {};

	drawInfo.DebugDrawType = eDebugDrawType::FillRect2D;
	drawInfo.WorldPos = worldPos;
	drawInfo.Scale = Vector3(rectScale.x, rectScale.y, 1.f);
	drawInfo.Rotation = Vector3::Zero;
	drawInfo.DrawTime = drawTime;
	drawInfo.FillColor = fillColor;

	mDebugDrawInfos.push_back(drawInfo);
}

void DebugRenderer2D::DrawFillRect2D2(const Vector3& wolrdLeftUpPos,
	const Vector3& worldRightDownPos,
	const float drawTime, const Vector4& fillColor)
{
	const Vector3 WORLD_POS = (wolrdLeftUpPos + worldRightDownPos) * 0.5f;
	const Vector3 RECT_SCALE_3D = worldRightDownPos - wolrdLeftUpPos;

	DrawFillRect2D(WORLD_POS, Vector2(RECT_SCALE_3D.x, RECT_SCALE_3D.y), drawTime, fillColor);
}

void DebugRenderer2D::DrawCircle2D(const Vector3& worldPos,
	float raduis,
	const float drawTime, const Vector4& outLineColor)
{
	tDebugDrawInfo drawInfo = {};

	drawInfo.DebugDrawType = eDebugDrawType::Circle2D;
	drawInfo.WorldPos = worldPos;
	drawInfo.Scale = Vector3(raduis * 2.f, raduis * 2.f, 1.f);
	drawInfo.Rotation = Vector3::Zero;
	drawInfo.DrawTime = drawTime;
	drawInfo.OutLineColor = outLineColor;

	mDebugDrawInfos.push_back(drawInfo);
}

void DebugRenderer2D::DrawFillCircle2D(const Vector3& worldPos,
	float raduis,
	const float drawTime, const Vector4& fillColor)
{
	tDebugDrawInfo drawInfo = {};

	drawInfo.DebugDrawType = eDebugDrawType::FillCircle2D;
	drawInfo.WorldPos = worldPos;
	drawInfo.Scale = Vector3(raduis * 2.f, raduis * 2.f, 1.f);
	drawInfo.Rotation = Vector3::Zero;
	drawInfo.DrawTime = drawTime;
	drawInfo.FillColor = fillColor;

	mDebugDrawInfos.push_back(drawInfo);
}

void DebugRenderer2D::DrawLine2D(const Vector3& startPos,
	const Vector3& endPos,
	const float drawTime, const Vector4& lineColor)
{
	tDebugDrawInfo drawInfo = {};

	const Vector3 pivot = (startPos + endPos) * 0.5f;
	const Vector3 dist = endPos - startPos;
	const Vector3 rotation = Vector3(0.f, 0.f, Rad2Deg(atan2f(dist.y, dist.x)));
	const Vector3 scale = Vector3(dist.Length(), 1.f, 1.f);

	drawInfo.DebugDrawType = eDebugDrawType::Line2D;
	drawInfo.WorldPos = pivot;
	drawInfo.Scale = scale;
	drawInfo.Rotation = rotation;
	drawInfo.DrawTime = drawTime;
	drawInfo.OutLineColor = lineColor;

	mDebugDrawInfos.push_back(drawInfo);
}

void DebugRenderer2D::DrawLine2D2(const Vector3& startPos,
	const Vector2& direction,
	const float length,
	const float drawTime, const Vector4& lineColor)
{
	Vector2 directionNorm = direction;
	directionNorm.Normalize();
	const Vector3 END_POS = startPos + (directionNorm * length);

	DrawLine2D(startPos, END_POS, drawTime, lineColor);
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

	for (tDebugDrawInfo& drawInfo : mDebugDrawInfos)
	{
		const tDebugMaterial& debugMat =
			mDebugMaterial[static_cast<UINT>(drawInfo.DebugDrawType)];

		const Mesh* const P_MESH = debugMat.debugMesh;
		const Shader* const P_SHADER = debugMat.debugShader;

		Assert(P_MESH, WCHAR_IS_NULLPTR);
		Assert(P_SHADER, WCHAR_IS_NULLPTR);

		Vector3 worldMousePos = helper::WindowScreenMouseToWorld3D(camera);
		worldMousePos = Vector3(worldMousePos.x, -worldMousePos.y, worldMousePos.z);
		CBTransform.World = Transform::CreateWorldMatrix(drawInfo.WorldPos, drawInfo.Rotation, drawInfo.Scale);
		gGraphicDevice->BindMesh(P_MESH);

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
			renderLine2D(drawInfo);
			break;

		case eDebugDrawType::FillRect2D:
			renderFill2D(drawInfo);
			break;

		case eDebugDrawType::Circle2D:
			renderLine2D(drawInfo);
			break;

		case eDebugDrawType::FillCircle2D:
			renderFill2D(drawInfo);
			break;

		case eDebugDrawType::Line2D:
			renderLine2D(drawInfo);
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

void DebugRenderer2D::renderLine2D(const tDebugDrawInfo& drawInfo)
{
	tCBDebugInfo CBRectInfo = {};
	{
		CBRectInfo.Color_1 = drawInfo.OutLineColor;

		gGraphicDevice->PassCB(eCBType::DebugInfo, sizeof(CBRectInfo), &CBRectInfo);
		gGraphicDevice->BindCB(eCBType::DebugInfo, eShaderBindType::PS);
	}
}

void DebugRenderer2D::renderFill2D(const tDebugDrawInfo& drawInfo)
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
