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
#include "DebugRenderer2D.h"

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

void RenderTargetRenderer::DrawRect2D(const Vector3& WORLD_POS, const Vector2& RECT_SCALE, const float DRAW_TIME)
{
	mDebugRenderer->DrawWorld2DRect(WORLD_POS, RECT_SCALE, DRAW_TIME);
}

void RenderTargetRenderer::DrawRect2D2(const Vector3& WORLD_LEFT_UP_POS,
	const Vector3& WORLD_RIGHT_BOTTOM_POS,
	const float DRAW_TIME)
{
	const Vector3 WORLD_POS = (WORLD_LEFT_UP_POS + WORLD_RIGHT_BOTTOM_POS) * 0.5f;
	const Vector3 RECT_SCALE_3D = WORLD_RIGHT_BOTTOM_POS - WORLD_LEFT_UP_POS;

	mDebugRenderer->DrawWorld2DRect(WORLD_POS, Vector2(RECT_SCALE_3D.x, RECT_SCALE_3D.y), DRAW_TIME);

}

void RenderTargetRenderer::DrawGrid2D(const Vector3& WORLD_POS, 
	const Vector2& XY_SIZE, 
	const Vector2& XY_COUNT, 
	const float DRAW_TIME)
{
	mDebugRenderer->DrawGrid2D(WORLD_POS, XY_SIZE, XY_COUNT, DRAW_TIME);
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
	std::vector<RenderComponent*>& renderObjects = mRenderComponentArrays[static_cast<UINT>(RENDER_PRIORITY_TYPE)];

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
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView,
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView)
{
	gGraphicDevice->ClearRenderTarget(RENDER_TARGET_WIDTH, RENDER_TARGET_HEIGHT, BG_COLOR, renderTargetView, depthStencilView);

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
