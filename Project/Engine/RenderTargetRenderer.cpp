#include "pch.h"
#include "RenderTargetRenderer.h"
#include "Shader.h"
#include "Transform.h"
#include "Material.h"
#include "CBCollection.h"
#include "StructConstantBuffer.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "RenderComponent.h"


RenderTargetRenderer::RenderTargetRenderer()
	: mCameras{ 0, }
	, mRenderComponentArrays()
{
	for (auto& renderObjectArray : mRenderComponentArrays)
	{
		renderObjectArray.reserve(100);
	}
}

RenderTargetRenderer::~RenderTargetRenderer()
{
}

void RenderTargetRenderer::RegisterRenderCamera(Camera* const camera)
{
	const Camera::eCameraType type = camera->GetCameraType();

	Assert(camera, WCHAR_IS_NULLPTR);
	Assert(type != Camera::eCameraType::End, WCHAR_IS_INVALID_TYPE);
	Assert(!mCameras[static_cast<UINT>(type)], WCHAR_IS_NOT_NULLPTR);

	mCameras[static_cast<UINT>(type)] = camera;
}

void RenderTargetRenderer::RegisterRenderComponent(RenderComponent* const renderComponent)
{
	Assert(renderComponent, WCHAR_IS_NULLPTR);

	const eRenderPriorityType type = renderComponent->GetMaterial()->GetRenderType();
	mRenderComponentArrays[static_cast<UINT>(type)].push_back(renderComponent);
}

void RenderTargetRenderer::zSortRenderObjectArray(const eRenderPriorityType type)
{
	std::vector<RenderComponent*>& renderObjects = mRenderComponentArrays[static_cast<UINT>(type)];

	std::sort(renderObjects.begin(), renderObjects.end(), [](RenderComponent* const lhs, RenderComponent* const rhs)
		{
			const Transform* const lhsTransform = lhs->GetComponent<Transform>();
			const Transform* const rhsTransform = rhs->GetComponent<Transform>();
			return lhsTransform->GetPosition().z < rhsTransform->GetPosition().z;
		});
}

void RenderTargetRenderer::Render(const UINT screenWidth,
	const UINT screenHeight,
	const FLOAT bgColor[4],
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView,
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView)
{
	gGraphicDevice->ClearRenderTarget(screenWidth, screenHeight, bgColor, renderTargetView, depthStencilView);

	//알파블렌딩 Z솔트가 필요할떄 적용한다.
	//zSortRenderObjectArray(eRenderType::Transparent);

	for (const Camera* const camera : mCameras)
	{
		if (nullptr == camera)
		{
			continue;
		}

		const UINT cameraLayerMask = camera->GetLayerMask();

		for (auto& renderObjectArray : mRenderComponentArrays)
		{
			for (RenderComponent* const renderComponent : renderObjectArray)
			{
				const UINT renderObjectLayer = static_cast<UINT>(renderComponent->GetOwner()->GetLayer());

				if (cameraLayerMask & (1 << renderObjectLayer))
				{
					renderComponent->render(camera);

				}
			}
		}
	}

	for (auto& camera : mCameras)
	{
		camera = nullptr;
	}

	for (auto& renderComponentArray : mRenderComponentArrays)
	{
		renderComponentArray.clear();
	}
}
