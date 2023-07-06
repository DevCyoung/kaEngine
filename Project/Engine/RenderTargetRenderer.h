#pragma once
#include <d3d11.h>
#include "Singleton.h"
#include "EnumRenderType.h"
#include "Camera.h"

class RenderComponent;
class Camera;
class DebugRenderer2D;
class RenderTargetRenderer
{
	friend class Camera;
	friend class RenderComponent;

public:
	RenderTargetRenderer();
	virtual ~RenderTargetRenderer();

	void Render(const UINT RENDER_TARGET_WIDTH,
		const UINT RENDER_TARGET_HEIGHT,
		const FLOAT BG_COLOR[4],
		ID3D11RenderTargetView** const ppRenderTargetView,
		ID3D11DepthStencilView** const ppDepthStencilView);

	Camera* GetRegisteredRenderCamera(const Camera::eCameraPriorityType type) const
	{
		Assert(type != Camera::eCameraPriorityType::End, WCHAR_IS_INVALID_TYPE);
		Assert(mCameras[static_cast<UINT>(type)], WCHAR_IS_NULLPTR);

		return mCameras[static_cast<UINT>(type)];
	}

	DebugRenderer2D* GetDebugRenderer() const { Assert(mDebugRenderer, WCHAR_IS_NULLPTR); return mDebugRenderer; }			

private:
	void RegisterRenderCamera(Camera* const camera);
	void RegisterRenderComponent(RenderComponent* const renderComponent);
	void zSortRenderObjectArray(const eRenderPriorityType RENDER_PRIORITY_TYPE);

private:
	DebugRenderer2D* mDebugRenderer;
	Camera* mCameras[static_cast<UINT>(Camera::eCameraPriorityType::End)];
	std::vector<RenderComponent*> mRenderComponentArrays[static_cast<UINT>(eRenderPriorityType::End)];
};
