#include "pch.h"
#include "MeshRenderer.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "CBCollection.h"
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Textrue.h"
#include "Shader.h"
#include "StructConstantBuffer.h"
#include "Camera.h"

MeshRenderer::MeshRenderer()
	: Component(eComponentType::MeshRenderer)
	, mMesh(nullptr)
	, mMaterial(nullptr)
	, mRenderTarget(nullptr)
	, mTestColor(Vector4::One)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::initialize()
{
}

void MeshRenderer::update()
{

}

void MeshRenderer::lateUpdate()
{
}

void MeshRenderer::render()
{
	Assert(mMesh, WCHAR_IS_NULLPTR);
	Assert(mMaterial, WCHAR_IS_NULLPTR);

	const Camera* const mainCamera = Camera::GetMainCamera();
	tTransform tTransformMatrix = {};
	tTransformMatrix.mWorld = GetOwner()->GetComponent<Transform>()->GetWorldMatrix();
	tTransformMatrix.mView = mainCamera->GetView();
	tTransformMatrix.mProj = mainCamera->GetProjection();
	gGraphicDevice->PassCB(eCBType::Transform, sizeof(tTransformMatrix), &tTransformMatrix);
	gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);

	tColorInfo tColorInfo = {};
	tColorInfo.mColor = mTestColor;
	gGraphicDevice->PassCB(eCBType::ColorInfo, sizeof(tColorInfo), &tColorInfo);
	gGraphicDevice->BindCB(eCBType::ColorInfo, eShaderBindType::PS);

	gGraphicDevice->BindIA(mMaterial->mShader);
	gGraphicDevice->BindPS(mMaterial->mShader);
	gGraphicDevice->BindVS(mMaterial->mShader);
	gGraphicDevice->BindBS(mMaterial->mShader->GetBSType());
	gGraphicDevice->BindDS(mMaterial->mShader->GetDSType());
	gGraphicDevice->BindRS(mMaterial->mShader->GetRSType());
	gGraphicDevice->BindTexture(eShaderBindType::PS, 0, mMaterial->mTexture);
	gGraphicDevice->BindMesh(mMesh);
	gGraphicDevice->Draw(0, mMesh);
}