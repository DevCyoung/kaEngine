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

namespace engine
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
		, mMesh(nullptr)
		, mMaterial(nullptr)
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
		assert(mMesh);
		assert(mMaterial);

		const Transform* const obj = GetOwner()->GetComponent<Transform>();

		const Vector3 objPos = obj->GetPosition();
		const Vector4 constPosition(objPos.x, objPos.y, objPos.z, 1.f);

		gGraphicDevice->PassCB(eCBType::Transform, &constPosition, sizeof(Vector4));
		gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);


		gGraphicDevice->BindIA(mMaterial->mShader);
		gGraphicDevice->BindPS(mMaterial->mShader);
		gGraphicDevice->BindVS(mMaterial->mShader);
		gGraphicDevice->BindTexture(mMaterial->mTexture, 0, eShaderBindType::PS);

		gGraphicDevice->BindMesh(mMesh);
		gGraphicDevice->Draw(mMesh, 0);
	}
}
