#include "pch.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "Material.h"
#include "Textrue.h"
#include "Shader.h"
#include "CBCollection.h"
#include "StructConstantBuffer.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "Transform.h"


SpriteRenderer::SpriteRenderer()
	: RenderComponent(eComponentType::SpriteRenderer)	
	, mTestColor(Vector4::One)
	, testX(Vector4::One)
	, bColorInfo(0)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::initialize()
{
}

void SpriteRenderer::update()
{	
	RenderComponent::update();
}

void SpriteRenderer::lateUpdate()
{
}

void SpriteRenderer::render(const Camera* const camera)
{
	Assert(mMesh, WCHAR_IS_NULLPTR);
	Assert(mMaterial, WCHAR_IS_NULLPTR);
	Assert(camera, WCHAR_IS_NULLPTR);

	tCBTransform tTrans = {};
	{
		Vector3 scale(mMaterial->GetTexture()->GetWidth(), mMaterial->GetTexture()->GetHeight(), 1.f);
		Matrix scaleMtrix = Matrix::CreateScale(scale);

		tTrans.mWorld = scaleMtrix * GetComponent<Transform>()->GetWorldMatrix();
		tTrans.mView = camera->GetView();
		tTrans.mProj = camera->GetProjection();
	}
	gGraphicDevice->PassCB(eCBType::Transform, sizeof(tTrans), &tTrans);
	gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);

	//FIXME: Material Info 범용성있는 방법으로 수정
	tCBColorInfo colorInfo = {};
	{
		colorInfo.bUseColor = bColorInfo;
		colorInfo.mColor = testX;

		gGraphicDevice->PassCB(eCBType::ColorInfo, sizeof(colorInfo), &colorInfo);
		gGraphicDevice->BindCB(eCBType::ColorInfo, eShaderBindType::PS);
	}

	gGraphicDevice->BindMesh(mMesh);
	gGraphicDevice->BindIA(mMaterial->GetShader());
	gGraphicDevice->BindPS(mMaterial->GetShader());
	gGraphicDevice->BindVS(mMaterial->GetShader());
	gGraphicDevice->BindBS(mMaterial->GetShader()->GetBSType());
	gGraphicDevice->BindDS(mMaterial->GetShader()->GetDSType());
	gGraphicDevice->BindRS(mMaterial->GetShader()->GetRSType());
	gGraphicDevice->BindTexture(eShaderBindType::PS, 0, mMaterial->GetTexture());
	gGraphicDevice->Draw(mMesh);
}
