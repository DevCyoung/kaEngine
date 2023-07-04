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
	enum class eCameraType
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
	float GetSize() const { return mSize; }
	float GetAspectRatio() const { return mAspectRatio; }
	const Matrix& GetView() const { return mView; }
	const Matrix& GetProjection() const { return mProjection; }
	eCameraType GetCameraType () const { return mCameraType; }
	UINT GetLayerMask() const { return mLayerMask; }
	eProjectionType GetProjectiontType() const { return mProjectionType; }

	void SetRenderTargetRenderer(RenderTargetRenderer* const renderTargetRenderer) 
	{ 
		Assert(renderTargetRenderer, WCHAR_IS_NULLPTR);
		Assert(!mRenderTargetRenderer, WCHAR_IS_NOT_NULLPTR);

		mRenderTargetRenderer = renderTargetRenderer; 
	}
	void SetFOV(const float FOVDegree) { mFOV = FOVDegree; }
	void SetNear(const float cameraNear) { mNear = cameraNear; }
	void SetFar(const float cameraFar) { mFar = cameraFar; }
	void SetCameraSize(const float cameraSize) { mSize = cameraSize; }
	void SetScreenSize(const Vector2& screenSize) { mScreenSize = screenSize; };
	void SetCameraType(const eCameraType cameraType) { mCameraType = cameraType; }
	void SetProjectiontType(const eProjectionType projectionType) { mProjectionType = projectionType; }

	void TurnOnLayer(const  eLayerType layer)  { mLayerMask |=  (1 <<  static_cast<UINT>(layer)); }
	void TurnOffLayer(const eLayerType layer)  { mLayerMask &= ~(1 <<  static_cast<UINT>(layer)); }

	void TurnOnAllLayer()  { mLayerMask = 0XFFFFFFFF; }
	void TurnOffAllLayer() { mLayerMask = 0; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	

private:
	RenderTargetRenderer* mRenderTargetRenderer;

	Vector2 mScreenSize;

	UINT mLayerMask;

	float mNear;
	float mFar;
	float mFOV;
	float mSize;
	float mAspectRatio;

	Matrix mView;
	Matrix mProjection;
	eProjectionType mProjectionType;
	eCameraType mCameraType;
};
