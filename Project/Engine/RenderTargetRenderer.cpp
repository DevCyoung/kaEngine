#include "pch.h"
#include "RenderTargetRenderer.h"
#include "DebugRenderer2D.h"
#include "Transform.h"
#include "Camera.h"
#include "RenderComponent.h"
#include "Light2D.h"
#include "StructuredBuffer.h"
#include "Material.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "Transform.h"

#include "EnumShaderBindStage.h"

#include "CBCollection.h"
#include "StructConstantBuffer.h"
#include "TimeManager.h"

RenderTargetRenderer::RenderTargetRenderer()
	: mDebugRenderer(new DebugRenderer2D())
	, mCameras{ 0, }
	, mRenderComponentsArray{}
	, mLight2DInfos()
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

void RenderTargetRenderer::registerLightInfo(const tLightInfo& light2DInfo)
{
	mLight2DInfos.push_back(light2DInfo);
}

void RenderTargetRenderer::zSortRenderObjectArray(const eRenderPriorityType renderPriorityType)
{
	auto& renderObjects = mRenderComponentsArray[static_cast<UINT>(renderPriorityType)];

	std::sort(renderObjects.begin(), renderObjects.end(), [](RenderComponent* const lhs, RenderComponent* const rhs)
		{
			const Transform* const lhsTransform = lhs->GetOwner()->GetComponent<Transform>();
			const Transform* const rhsTransform = rhs->GetOwner()->GetComponent<Transform>();
			return lhsTransform->GetPosition().z < rhsTransform->GetPosition().z;
		});
}

void RenderTargetRenderer::Render(const UINT renderTargetWidth,
	const UINT renderTargetHeight,
	ID3D11RenderTargetView** const ppRenderTargetView,
	ID3D11DepthStencilView* const depthStencilView) const
{
	//렌더 준비단계 
	gGraphicDevice->BindRenderTarget(renderTargetWidth,
		renderTargetHeight,
		ppRenderTargetView,
		depthStencilView);

	const void* const P_LIGHT_DATA = mLight2DInfos.data();
	if (nullptr != P_LIGHT_DATA)
	{
		gGraphicDevice->PassSB(eSBType::Light2D, sizeof(tLightInfo),
			static_cast<UINT>(mLight2DInfos.size()), P_LIGHT_DATA);

		gGraphicDevice->BindSB(eSBType::Light2D, eShaderBindType::PS);
	}

	tGlobalInfo globalInfo = {};

	globalInfo.Deltatime = gDeltaTime;
	globalInfo.Light2DCount = static_cast<UINT>(mLight2DInfos.size());
	globalInfo.GlobalTime = gGlobalTime;
		
	gGraphicDevice->PassCB(eCBType::GlobalInfo, sizeof(globalInfo), &globalInfo);
	gGraphicDevice->BindCB(eCBType::GlobalInfo, eShaderBindType::VS);
	gGraphicDevice->BindCB(eCBType::GlobalInfo, eShaderBindType::PS);


	//TODO: 알파블렌딩 Z솔트가 필요할떄 적용한다.
	//zSortRenderObjectArray(eRenderType::Transparent);

	for (const Camera* const P_CAMERA : mCameras)
	{
		if (nullptr == P_CAMERA)
		{
			continue;
		}

		const UINT CAMERA_PRIORITY = static_cast<UINT>(P_CAMERA->GetPriorityType());

		if (!(mCameraMask & (1 << CAMERA_PRIORITY)))
		{
			continue;
		}

		const UINT CAMERA_LAYER_MASK = P_CAMERA->GetLayerMask();

		for (auto& renderComponents : mRenderComponentsArray)
		{
			for (RenderComponent* const renderComponent : renderComponents)
			{
				const UINT GAMEOBJECT_LAYER = static_cast<UINT>(renderComponent->GetOwner()->GetLayer());

				if (CAMERA_LAYER_MASK & (1 << GAMEOBJECT_LAYER))
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

	//TODO: 추후에 다시확인
	//for (auto& camera : mCameras)
	//{
	//	camera = nullptr;
	//}

	for (auto& renderComponents : mRenderComponentsArray)
	{
		renderComponents.clear();
	}

	mLight2DInfos.clear();
}
