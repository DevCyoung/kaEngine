#pragma once
#include "Component.h"

REGISTER_COMPONENT_TYPE(Camera);

class Camera : public Component
{
	enum class eProjectionType
	{
		Perspective,
		Orthographic,
	};
public:
	Camera();
	virtual ~Camera();
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	void SetFOV(const float fov) { mFOV = fov; }
	void SetNear(const float _near) { mNear = _near; }
	void SetFar(const float _far) { mFar = _far; }
	void SetAspectRatio(const float aspectRatio) { mAspectRatio = aspectRatio; }

	float GetFOV() const { return mFOV; }
	float GetNear() const { return mNear; }
	float GetFar() const { return mFar; }
	float GetAspectRatio() const { return mAspectRatio; }

	const Matrix& GetView() const { return mView; }
	const Matrix& GetProjection() const { return mProjection; }

	static Camera* GetMainCameraOrNull() { return sMainCamera; }
	static Camera* GetMainCamera() { Assert(sMainCamera, WCHAR_IS_NULLPTR); return sMainCamera; }
	static void SetMainCamera(Camera* const camera) { Assert(camera, WCHAR_IS_NULLPTR); sMainCamera = camera; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;

private:
	inline static Camera* sMainCamera = nullptr;

	float mNear;
	float mFar;
	float mFOV;
	float mSize;
	float mAspectRatio;
	Matrix mView;
	Matrix mProjection;
	eProjectionType mProjectionType;
};

