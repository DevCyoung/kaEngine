#include "pch.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "MeshCollection.h"
#include "ShaderCollection.h"
#include "CBCollection.h"
#include "Transform.h"

#include "EnumResourceTypeTexture.h"

namespace engine
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
		, mMeshType(eMeshType::Rect)
		, mShaderType(eShaderType::Default)
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
		const Transform* const obj = GetOwner()->GetComponent<Transform>();		

		const Vector3 objPos = obj->GetPosition();
		const Vector4 constPosition(objPos.x, objPos.y, objPos.z, 1.f);
		
		gGraphicDevice->PassCB(eCBType::Transform, &constPosition);
		gGraphicDevice->BindCB(eCBType::Transform, eShaderBindType::VS);

		gGraphicDevice->BindIA(mShaderType);
		gGraphicDevice->BindPS(mShaderType);
		gGraphicDevice->BindVS(mShaderType);

		gGraphicDevice->BindTexture(eResTexture::Fighter, eShaderBindType::PS);

		gGraphicDevice->BindMesh(mMeshType);
		gGraphicDevice->Draw(mMeshType, 0);
	}
}