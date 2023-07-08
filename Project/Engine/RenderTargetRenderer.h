#pragma once
#include <d3d11.h>
#include "Singleton.h"
#include "EnumRenderType.h"

class Camera;
class RenderComponent;
class DebugRenderer2D;

enum class eCameraPriorityType;

class RenderTargetRenderer
{
	friend class Camera;
	friend class RenderComponent;

public:
	RenderTargetRenderer();
	virtual ~RenderTargetRenderer();

	void Render(const UINT renderTargetWidth,
		const UINT renderTargetHeight,
		const FLOAT backgroundColor[4],
		ID3D11RenderTargetView** const ppRenderTargetView,
		ID3D11DepthStencilView* const depthStencilView);

	Camera* GetRegisteredRenderCamera(const eCameraPriorityType cameraPriorityType) const
	{		
		Assert(mCameras[static_cast<UINT>(cameraPriorityType)], WCHAR_IS_NULLPTR);

		return mCameras[static_cast<UINT>(cameraPriorityType)];
	}

	DebugRenderer2D* GetDebugRenderer() const { Assert(mDebugRenderer, WCHAR_IS_NULLPTR); return mDebugRenderer; }

private:
	void registerRenderCamera(Camera* const camera);
	void registerRenderComponent(RenderComponent* const renderComponent);
	void zSortRenderObjectArray(const eRenderPriorityType renderPriorityType);

private:
	DebugRenderer2D* mDebugRenderer;
	Camera* mCameras[static_cast<UINT>(eCameraPriorityType::End)];
	std::vector<RenderComponent*> mRenderComponentsArray[static_cast<UINT>(eRenderPriorityType::End)];
};
