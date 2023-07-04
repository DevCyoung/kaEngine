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
#include "DebugRenderer.h"

RenderTargetRenderer::RenderTargetRenderer()
	: mDebugRenderer(nullptr)
	, mCameras{ 0, }
	, mRenderComponentArrays()
{
	mDebugRenderer = new DebugRenderer();

	for (auto& renderObjectArray : mRenderComponentArrays)
	{
		renderObjectArray.reserve(100);
	}
}

RenderTargetRenderer::~RenderTargetRenderer()
{
	SAFE_DELETE_POINTER(mDebugRenderer);
}

void RenderTargetRenderer::DrawRect(const Vector2& WORLD_POS, const Vector2& RECT_SCALE, const float DRAW_TIME)
{	
	mDebugRenderer->DrawWorld2DRect(WORLD_POS, RECT_SCALE, DRAW_TIME);
}

void RenderTargetRenderer::DrawRect2(const Vector2& WORLD_LEFT_UP_POS, 
	const Vector2& WORLD_RIGHT_BOTTOM_POS, 
	const float DRAW_TIME)
{
	const Vector2 WORLD_POS = (WORLD_LEFT_UP_POS + WORLD_RIGHT_BOTTOM_POS) * 0.5f;
	const Vector2 RECT_SCALE = WORLD_RIGHT_BOTTOM_POS - WORLD_LEFT_UP_POS;

	mDebugRenderer->DrawWorld2DRect(WORLD_POS, RECT_SCALE, DRAW_TIME);

}

void RenderTargetRenderer::RegisterRenderCamera(Camera* const camera)
{
	const Camera::eCameraPriorityType type = camera->GetCameraType();

	Assert(camera, WCHAR_IS_NULLPTR);
	Assert(type != Camera::eCameraPriorityType::End, WCHAR_IS_INVALID_TYPE);
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

	const Camera* const P_MAIN_CAMERA = mCameras[static_cast<UINT>(Camera::eCameraPriorityType::Main)];

	mDebugRenderer->Render(P_MAIN_CAMERA);

	for (auto& camera : mCameras)
	{
		camera = nullptr;
	}

	for (auto& renderComponentArray : mRenderComponentArrays)
	{
		renderComponentArray.clear();
	}
}
