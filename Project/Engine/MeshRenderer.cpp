#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Material.h"
#include "Textrue.h"
#include "Shader.h"
#include "CBCollection.h"
#include "StructConstantBuffer.h"
#include "GameObject.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "RenderManager.h"
#include "Transform.h"

MeshRenderer::MeshRenderer()
	: Component(eComponentType::MeshRenderer)
	, mMesh(nullptr)
	, mMaterial(nullptr)
	, mRenderTarget(nullptr)
	, mTestColor(Vector4::One)
	, testX(Vector4::One)
	, bColorInfo(0)
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
	const eRenderType type = mMaterial->GetRenderType();

	RenderManager::GetInstance()->RegisterRenderGameObject(type, GetOwner());
}

void MeshRenderer::lateUpdate()
{		
}

void MeshRenderer::render()
{
	Assert(mMesh, WCHAR_IS_NULLPTR);
	Assert(mMaterial, WCHAR_IS_NULLPTR);
	const Camera* const camera = RenderManager::GetInstance()->GetCurrentCalculateCamera();

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

	tCBColorInfo colorInfo = {};
	{
		colorInfo.bUseColor = bColorInfo;
		colorInfo.mColor = testX;

		gGraphicDevice->PassCB(eCBType::ColorInfo, sizeof(colorInfo), &colorInfo);
		gGraphicDevice->BindCB(eCBType::ColorInfo, eShaderBindType::PS);
	}
	

	gGraphicDevice->BindMesh(mMesh);
	gGraphicDevice->BindIA(mMaterial->mShader);
	gGraphicDevice->BindPS(mMaterial->mShader);
	gGraphicDevice->BindVS(mMaterial->mShader);
	gGraphicDevice->BindBS(mMaterial->mShader->GetBSType());
	gGraphicDevice->BindDS(mMaterial->mShader->GetDSType());
	gGraphicDevice->BindRS(mMaterial->mShader->GetRSType());
	gGraphicDevice->BindTexture(eShaderBindType::PS, 0, mMaterial->mTexture);
	gGraphicDevice->Draw(mMesh);
}