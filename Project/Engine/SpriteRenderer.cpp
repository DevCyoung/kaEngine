#include "pch.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "Material.h"
#include "Textrue.h"
#include "Shader.h"
#include "CBCollection.h"
#include "StructBuffer.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "Transform.h"
#include "EnumSRV.h"

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

	tCBTransform CBTransform = {};
	{
		const Vector3& SCALE 
			= Vector3(mMaterial->GetTexture()->GetWidth(), mMaterial->GetTexture()->GetHeight(), 1.f);
		const Matrix& SCALE_MATRIX = Matrix::CreateScale(SCALE);

		CBTransform.World = SCALE_MATRIX * GetOwner()->GetComponent<Transform>()->GetWorldMatrix();
		CBTransform.View = camera->GetView();
		CBTransform.Proj = camera->GetProjection();

		gGraphicDevice->PassCB(eCBType::Transform, sizeof(CBTransform), &CBTransform);
		gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);
	}	

	//FIXME: Material Info 범용성있는 방법으로 수정
	tCBColorInfo CBColorInfo = {};
	{
		CBColorInfo.bUseColor = bColorInfo;
		CBColorInfo.Color = testX;

		gGraphicDevice->PassCB(eCBType::ColorInfo, sizeof(CBColorInfo), &CBColorInfo);
		gGraphicDevice->BindCB(eCBType::ColorInfo, eShaderBindType::PS);
	}

	gGraphicDevice->BindMesh(mMesh);
	gGraphicDevice->BindIA(mMaterial->GetShader());
	gGraphicDevice->BindPS(mMaterial->GetShader());
	gGraphicDevice->BindVS(mMaterial->GetShader());
	gGraphicDevice->BindBS(mMaterial->GetShader()->GetBSType());
	gGraphicDevice->BindDS(mMaterial->GetShader()->GetDSType());
	gGraphicDevice->BindRS(mMaterial->GetShader()->GetRSType());	
	gGraphicDevice->BindSRV(eShaderBindType::PS, static_cast<UINT>(eSRVTpye::Sprite2D), mMaterial->GetTexture());
	gGraphicDevice->Draw(mMesh);
}
