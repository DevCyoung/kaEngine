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
	void Set3DFOV(const float FOV_DEGREE) { mFOV = FOV_DEGREE; }
	void SetNear(const float CAMERA_NEAR) { mNear = CAMERA_NEAR; }
	void SetFar(const float CAMERA_FAR) { mFar = CAMERA_FAR; }
	void SetCamera2DSize(const float CAMERA_2D_SIZE) { mSize = CAMERA_2D_SIZE; }
	void SetRenderTargetSize(const Vector2& RENDER_TARGET_SIZE) { mRenderTargetSize = RENDER_TARGET_SIZE; };
	void SetCameraType(const eCameraPriorityType CAMERA_TYPE) { mCameraType = CAMERA_TYPE; }
	void SetProjectiontType(const eProjectionType PROJECTION_TYPE) { mProjectionType = PROJECTION_TYPE; }

	void TurnOnLayer(const  eLayerType LAYER_TYPE)  { mLayerMask |=  (1 <<  static_cast<UINT>(LAYER_TYPE)); }
	void TurnOffLayer(const eLayerType LAYER_TYPE)  { mLayerMask &= ~(1 <<  static_cast<UINT>(LAYER_TYPE)); }

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
