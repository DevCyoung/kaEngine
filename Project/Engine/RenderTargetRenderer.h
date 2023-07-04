#pragma once
#include <d3d11.h>
#include "Singleton.h"
#include "EnumRenderType.h"
#include "Camera.h"

class RenderComponent;
class Camera;

class RenderTargetRenderer
{
	friend class Camera;
	friend class RenderComponent;

public:
	RenderTargetRenderer();
	virtual ~RenderTargetRenderer();

	void Render(const UINT screenWidth,
		const UINT screenHeight,
		const FLOAT bgColor[4],
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView,
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView);

	Camera* GetRegisteredRenderCamera(const Camera::eCameraType type) const
	{
		Assert(type != Camera::eCameraType::End, WCHAR_IS_INVALID_TYPE);
		Assert(mCameras[static_cast<UINT>(type)], WCHAR_IS_NULLPTR);

		return mCameras[static_cast<UINT>(type)];
	}

private:
	void RegisterRenderCamera(Camera* const camera);

	void RegisterRenderComponent(RenderComponent* const renderComponent);

	void zSortRenderObjectArray(const eRenderPriorityType type);


private:
	Camera* mCameras[static_cast<UINT>(Camera::eCameraType::End)];
	std::vector<RenderComponent*> mRenderComponentArrays[static_cast<UINT>(eRenderPriorityType::End)];
};
