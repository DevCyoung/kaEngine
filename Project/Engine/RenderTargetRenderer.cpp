#include "pch.h"
#include "RenderTargetRenderer.h"
#include "DebugRenderer2D.h"
#include "Transform.h"
#include "Camera.h"
#include "RenderComponent.h"
#include "Material.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"

RenderTargetRenderer::RenderTargetRenderer()
	: mDebugRenderer(new DebugRenderer2D())
	, mCameras{ 0, }
	, mRenderComponentsArray()
	, mbDebugRender(true)
	, mCameraMask(0XFFFFFFFF)
{	
	for (auto& renderObjectArray : mRenderComponentsArray)
	{
		renderObjectArray.reserve(100);
	}
}

RenderTargetRenderer::~RenderTargetRenderer()
{
	SAFE_DELETE_POINTER(mDebugRenderer);
}

void RenderTargetRenderer::registerRenderCamera(Camera* const camera)
{
	const eCameraPriorityType CAMERA_PRIORITY_TYPE = camera->GetPriorityType();

	Assert(camera, WCHAR_IS_NULLPTR);
	Assert(CAMERA_PRIORITY_TYPE != eCameraPriorityType::End, WCHAR_IS_INVALID_TYPE);
	Assert(!mCameras[static_cast<UINT>(CAMERA_PRIORITY_TYPE)], WCHAR_IS_NOT_NULLPTR);

	mCameras[static_cast<UINT>(CAMERA_PRIORITY_TYPE)] = camera;
}

void RenderTargetRenderer::registerRenderComponent(RenderComponent* const renderComponent)
{
	Assert(renderComponent, WCHAR_IS_NULLPTR);

	const eRenderPriorityType RENDER_PRIORITY_TYPE = renderComponent->GetMaterial()->GetRenderType();
	mRenderComponentsArray[static_cast<UINT>(RENDER_PRIORITY_TYPE)].push_back(renderComponent);
}

void RenderTargetRenderer::zSortRenderObjectArray(const eRenderPriorityType renderPriorityType)
{
	auto& renderObjects = mRenderComponentsArray[static_cast<UINT>(renderPriorityType)];

	std::sort(renderObjects.begin(), renderObjects.end(), [](RenderComponent* const lhs, RenderComponent* const rhs)
		{
			const Transform* const lhsTransform = lhs->GetComponent<Transform>();
			const Transform* const rhsTransform = rhs->GetComponent<Transform>();
			return lhsTransform->GetPosition().z < rhsTransform->GetPosition().z;
		});
}

void RenderTargetRenderer::Render(const UINT renderTargetWidth,
	const UINT renderTargetHeight,
	const FLOAT backgroundColor[4],
	ID3D11RenderTargetView** const ppRenderTargetView,
	ID3D11DepthStencilView* const depthStencilView) const
{
	gGraphicDevice->ClearRenderTarget(renderTargetWidth, renderTargetHeight, 
		backgroundColor, ppRenderTargetView, depthStencilView);

	//알파블렌딩 Z솔트가 필요할떄 적용한다.
	//zSortRenderObjectArray(eRenderType::Transparent);

	for (const Camera* const P_CAMERA : mCameras)
	{
		if (nullptr == P_CAMERA)
		{
			continue;
		}
		
		const UINT RENDER_PRIORITY = static_cast<UINT>(P_CAMERA->GetPriorityType());

		if (!(mCameraMask & (1 << RENDER_PRIORITY)))
		{
			continue;
		}

		const UINT CAMERA_LAYER_MASK = P_CAMERA->GetLayerMask();

		for (auto& renderComponents : mRenderComponentsArray)
		{
			for (RenderComponent* const renderComponent : renderComponents)
			{
				const UINT RENDER_OBJ_LAYER = static_cast<UINT>(renderComponent->GetOwner()->GetLayer());

				if (CAMERA_LAYER_MASK & (1 << RENDER_OBJ_LAYER))
				{
					renderComponent->render(P_CAMERA);
				}
			}
		}
	}

	const Camera* const P_MAIN_CAMERA = mCameras[static_cast<UINT>(eCameraPriorityType::Main)];

	if (mbDebugRender)
	{
		mDebugRenderer->render(P_MAIN_CAMERA);
	}	
}

void RenderTargetRenderer::flush()
{
	mDebugRenderer->flush();

	for (auto& camera : mCameras)
	{
		camera = nullptr;
	}

	for (auto& renderComponents : mRenderComponentsArray)
	{
		renderComponents.clear();
	}
}
