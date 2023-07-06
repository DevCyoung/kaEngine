#include "pch.h"
#include "RenderTargetRenderer.h"
#include "DebugRenderer2D.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "Material.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"

RenderTargetRenderer::RenderTargetRenderer()
	: mDebugRenderer(new DebugRenderer2D())
	, mCameras{ 0, }
	, mRenderComponentArrays()
{	
	for (auto& renderObjectArray : mRenderComponentArrays)
	{
		renderObjectArray.reserve(100);
	}
}

RenderTargetRenderer::~RenderTargetRenderer()
{
	SAFE_DELETE_POINTER(mDebugRenderer);
}

void RenderTargetRenderer::RegisterRenderCamera(Camera* const camera)
{
	const Camera::eCameraPriorityType CAMERA_PRIORITY_TYPE = camera->GetCameraType();

	Assert(camera, WCHAR_IS_NULLPTR);
	Assert(CAMERA_PRIORITY_TYPE != Camera::eCameraPriorityType::End, WCHAR_IS_INVALID_TYPE);
	Assert(!mCameras[static_cast<UINT>(CAMERA_PRIORITY_TYPE)], WCHAR_IS_NOT_NULLPTR);

	mCameras[static_cast<UINT>(CAMERA_PRIORITY_TYPE)] = camera;
}

void RenderTargetRenderer::RegisterRenderComponent(RenderComponent* const renderComponent)
{
	Assert(renderComponent, WCHAR_IS_NULLPTR);

	const eRenderPriorityType RENDER_PRIORITY_TYPE = renderComponent->GetMaterial()->GetRenderType();
	mRenderComponentArrays[static_cast<UINT>(RENDER_PRIORITY_TYPE)].push_back(renderComponent);
}

void RenderTargetRenderer::zSortRenderObjectArray(const eRenderPriorityType RENDER_PRIORITY_TYPE)
{
	auto& renderObjects = mRenderComponentArrays[static_cast<UINT>(RENDER_PRIORITY_TYPE)];

	std::sort(renderObjects.begin(), renderObjects.end(), [](RenderComponent* const lhs, RenderComponent* const rhs)
		{
			const Transform* const lhsTransform = lhs->GetComponent<Transform>();
			const Transform* const rhsTransform = rhs->GetComponent<Transform>();
			return lhsTransform->GetPosition().z < rhsTransform->GetPosition().z;
		});
}

void RenderTargetRenderer::Render(const UINT RENDER_TARGET_WIDTH,
	const UINT RENDER_TARGET_HEIGHT,
	const FLOAT BG_COLOR[4],
	ID3D11RenderTargetView** const ppRenderTargetView,
	ID3D11DepthStencilView** const ppDepthStencilView)
{
	gGraphicDevice->ClearRenderTarget(RENDER_TARGET_WIDTH, RENDER_TARGET_HEIGHT, 
		BG_COLOR, ppRenderTargetView, ppDepthStencilView);

	//알파블렌딩 Z솔트가 필요할떄 적용한다.
	//zSortRenderObjectArray(eRenderType::Transparent);

	for (const Camera* const P_CAMERA : mCameras)
	{
		if (nullptr == P_CAMERA)
		{
			continue;
		}

		const UINT CAMERA_LAYER_MASK = P_CAMERA->GetLayerMask();

		for (auto& renderObjectArray : mRenderComponentArrays)
		{
			for (RenderComponent* const renderComponent : renderObjectArray)
			{
				const UINT RENDER_OBJ_LAYER = static_cast<UINT>(renderComponent->GetOwner()->GetLayer());

				if (CAMERA_LAYER_MASK & (1 << RENDER_OBJ_LAYER))
				{
					renderComponent->render(P_CAMERA);
				}
			}
		}
	}

	const Camera* const P_MAIN_CAMERA = mCameras[static_cast<UINT>(Camera::eCameraPriorityType::Main)];
	mDebugRenderer->render(P_MAIN_CAMERA);

	for (auto& camera : mCameras)
	{
		camera = nullptr;
	}

	for (auto& renderComponentArray : mRenderComponentArrays)
	{
		renderComponentArray.clear();
	}
}
