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
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView,
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView);

	Camera* GetRegisteredRenderCamera(const Camera::eCameraPriorityType type) const
	{
		Assert(type != Camera::eCameraPriorityType::End, WCHAR_IS_INVALID_TYPE);
		Assert(mCameras[static_cast<UINT>(type)], WCHAR_IS_NULLPTR);

		return mCameras[static_cast<UINT>(type)];
	}

	void DrawRect2D(const Vector3& WORLD_POS, const Vector2& RECT_SCALE, const float DRAW_TIME);
	void DrawRect2D2(const Vector3& WORLD_LEFT_UP_POS, const Vector3& WORLD_RIGHT_BOTTOM_POS, const float DRAW_TIME);
	void DrawGrid2D(const Vector3& WORLD_POS, const Vector2& XY_SIZE, const Vector2& XY_COUNT, const float DRAW_TIME);


private:
	void RegisterRenderCamera(Camera* const camera);
	void RegisterRenderComponent(RenderComponent* const renderComponent);
	void zSortRenderObjectArray(const eRenderPriorityType RENDER_PRIORITY_TYPE);

private:
	DebugRenderer2D* mDebugRenderer;
	Camera* mCameras[static_cast<UINT>(Camera::eCameraPriorityType::End)];
	std::vector<RenderComponent*> mRenderComponentArrays[static_cast<UINT>(eRenderPriorityType::End)];
};
