#pragma once
#include "Component.h"

enum class eLayerType;
class RenderTargetRenderer;

REGISTER_COMPONENT_TYPE(Camera);

class Camera : public Component
{
public:
	enum class eProjectionType
	{
		Perspective,
		Orthographic,
		End
	};

public:
	enum class eCameraPriorityType
	{
		Main,
		UI,
		End
	};

public:
	Camera();
	virtual ~Camera();
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	float GetFOV() const { return mFOV; }
	float GetNear() const { return mNear; }
	float GetFar() const { return mFar; }
	float GetCameraSize() const { return mSize; }
	float GetAspectRatio() const { return mAspectRatio; }
	const Matrix& GetView() const { return mView; }
	const Matrix& GetProjection() const { return mProjection; }
	eCameraPriorityType GetCameraType () const { return mCameraType; }
	UINT GetLayerMask() const { return mLayerMask; }
	eProjectionType GetProjectiontType() const { return mProjectionType; }

	void SetRenderTargetRenderer(RenderTargetRenderer* const renderTargetRenderer) 
	{ 
		Assert(renderTargetRenderer, WCHAR_IS_NULLPTR);
		Assert(!mRenderTargetRenderer, WCHAR_IS_NOT_NULLPTR);

		mRenderTargetRenderer = renderTargetRenderer; 
	}
	void Set3DFOV(const float fov) { mFOV = fov; }
	void SetNear(const float cameraNear) { mNear = cameraNear; }
	void SetFar(const float cameraFar) { mFar = cameraFar; }
	void SetCamera2DSize(const float camera2DSize) { mSize = camera2DSize; }
	void SetRenderTargetSize(const Vector2& renderTargetSize) { mRenderTargetSize = renderTargetSize; };
	void SetCameraType(const eCameraPriorityType cameraPriorityType) { mCameraType = cameraPriorityType; }
	void SetProjectiontType(const eProjectionType projectionType) { mProjectionType = projectionType; }

	void TurnOnLayer(const  eLayerType layerType)  { mLayerMask |=  (1 <<  static_cast<UINT>(layerType)); }
	void TurnOffLayer(const eLayerType layerType)  { mLayerMask &= ~(1 <<  static_cast<UINT>(layerType)); }

	void TurnOnAllLayer()  { mLayerMask = 0XFFFFFFFF; }
	void TurnOffAllLayer() { mLayerMask = 0; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	

private:
	RenderTargetRenderer* mRenderTargetRenderer;

	Vector2 mRenderTargetSize;

	UINT mLayerMask;

	float mNear;
	float mFar;
	float mFOV;
	float mSize;
	float mAspectRatio;

	Matrix mView;
	Matrix mProjection;

	eProjectionType mProjectionType;
	eCameraPriorityType mCameraType;
};
