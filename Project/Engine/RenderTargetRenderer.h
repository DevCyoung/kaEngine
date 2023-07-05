#pragma once
#include <d3d11.h>
#include "Singleton.h"
#include "EnumRenderType.h"
#include "Camera.h"

class RenderComponent;
class Camera;
class DebugRenderer;
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

	Camera* GetRegisteredRenderCamera(const Camera::eCameraPriorityType type) const
	{
		Assert(type != Camera::eCameraPriorityType::End, WCHAR_IS_INVALID_TYPE);
		Assert(mCameras[static_cast<UINT>(type)], WCHAR_IS_NULLPTR);

		return mCameras[static_cast<UINT>(type)];
	}

	void DrawRect(const Vector3& WORLD_POS, const Vector2& RECT_SCALE, const float DRAW_TIME);
	void DrawRect2(const Vector3& WORLD_LEFT_UP_POS, const Vector3& WORLD_RIGHT_BOTTOM_POS, const float DRAW_TIME);

private:
	void RegisterRenderCamera(Camera* const camera);

	void RegisterRenderComponent(RenderComponent* const renderComponent);

	void zSortRenderObjectArray(const eRenderPriorityType type);


private:
	DebugRenderer* mDebugRenderer;

	Camera* mCameras[static_cast<UINT>(Camera::eCameraPriorityType::End)];
	std::vector<RenderComponent*> mRenderComponentArrays[static_cast<UINT>(eRenderPriorityType::End)];
};
