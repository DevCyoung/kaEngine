#pragma once
#include "Component.h"
enum class eLayerType;

REGISTER_COMPONENT_TYPE(Camera);

class Camera : public Component
{
	friend class RenderManager;
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
	UINT GetLayerMask() const { return mLayerMask; }
	eProjectionType GetProjectiontType() const { return mProjectionType; }

	void SetFOV(const float fov) { mFOV = fov; }
	void SetNear(const float _near) { mNear = _near; }
	void SetFar(const float _far) { mFar = _far; }
	void SetSize(const float size) { mSize = size; }
	void SetAspectRatio(const float aspectRatio) { mAspectRatio = aspectRatio; }	
	void SetCameraType(const eCameraType cameraType) { mCameraType = cameraType; }
	void SetProjectiontType(const eProjectionType projectionType) { mProjectionType = projectionType; }


	void TurnOnLayer(const  eLayerType layer)  { mLayerMask |=  (1 <<  static_cast<UINT>(layer)); }
	void TurnOffLayer(const eLayerType layer)  { mLayerMask &= ~(1 << static_cast<UINT>(layer)); }

	void TurnOnAllLayer() { mLayerMask = 0XFFFFFFFF; }
	void TurnOffAllLayer() { mLayerMask = 0; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;

private:
	inline static Camera* sMainCamera = nullptr;

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
