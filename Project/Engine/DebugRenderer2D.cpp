#include "pch.h"
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

DebugRenderer2D::DebugRenderer2D()
	: RenderComponent(eComponentType::DebugRenderer2D)
{
}

DebugRenderer2D::~DebugRenderer2D()
{
}

void DebugRenderer2D::initialize()
{
}

void DebugRenderer2D::update()
{
}

void DebugRenderer2D::lateUpdate()
{
}

void DebugRenderer2D::render(const Camera* const camera)
{
	Assert(mMesh, WCHAR_IS_NULLPTR);
	Assert(mMaterial, WCHAR_IS_NULLPTR);
	Assert(camera, WCHAR_IS_NULLPTR);

	tCBTransform tTrans = {};
	{
		tTrans.World = GetComponent<Transform>()->GetWorldMatrix();
		tTrans.View = camera->GetView();
		tTrans.Proj = camera->GetProjection();
	}
	gGraphicDevice->PassCB(eCBType::Transform, sizeof(tTrans), &tTrans);
	gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);

	gGraphicDevice->BindMesh(mMesh);
	gGraphicDevice->BindIA(mMaterial->GetShader());
	gGraphicDevice->BindPS(mMaterial->GetShader());
	gGraphicDevice->BindVS(mMaterial->GetShader());
	gGraphicDevice->BindBS(mMaterial->GetShader()->GetBSType());
	gGraphicDevice->BindDS(mMaterial->GetShader()->GetDSType());
	gGraphicDevice->BindRS(mMaterial->GetShader()->GetRSType());
	gGraphicDevice->Draw(mMesh);
}
