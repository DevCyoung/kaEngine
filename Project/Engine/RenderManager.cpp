#include "pch.h"
#include "RenderManager.h"
#include "Shader.h"
#include "Transform.h"
#include "Material.h"
#include "CBCollection.h"
#include "StructConstantBuffer.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"

RenderManager::RenderManager()
	: mCurrentCalculateCamera(nullptr)
	, mCameras{ 0, }
	, mRenderObjectArrays()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::zSortRenderObjectArray(const eRenderType type)
{
	std::vector<GameObject*>& renderObjects = mRenderObjectArrays[static_cast<UINT>(type)];

	std::sort(renderObjects.begin(), renderObjects.end(), [](GameObject* const lhs, GameObject* const rhs)
		{
			const Transform* const lhsTransform = lhs->GetComponent<Transform>();
			const Transform* const rhsTransform = rhs->GetComponent<Transform>();
			return lhsTransform->GetPosition().z < rhsTransform->GetPosition().z;
		});
}

void RenderManager::render()
{
	//알파블렌딩 Z솔트가 필요할떄 적용한다.
	//zSortRenderObjectArray(eRenderType::Transparent);

	for (const Camera* const camera : mCameras)
	{
		mCurrentCalculateCamera = nullptr;

		if (nullptr == camera)
		{
			continue;
		}

		mCurrentCalculateCamera = camera;

		const UINT cameraLayerMask = camera->GetLayerMask();		

		for (auto& renderObjectArray : mRenderObjectArrays)
		{
			for (GameObject* const renderObject : renderObjectArray)
			{
				const UINT renderObjectLayer = renderObject->GetLayer();

				if (cameraLayerMask & (1 << renderObjectLayer))
				{				
					renderObject->render();
				}
			}
		}		
	}

	mCurrentCalculateCamera = nullptr;

	for (auto& camera : mCameras)
	{
		camera = nullptr;
	}

	for (auto& renderObjects : mRenderObjectArrays)
	{
		renderObjects.clear();
	}
}
