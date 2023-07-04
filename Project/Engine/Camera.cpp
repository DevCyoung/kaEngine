#include "pch.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Engine.h"
#include "RenderTargetRenderer.h"
#include "EngineMath.h"

Camera::Camera()
	: Component(eComponentType::Camera)
	, mRenderTargetRenderer(nullptr)
	, mScreenSize(Vector2::Zero)
	, mLayerMask(0XFFFFFFFF)
	, mNear(1.0f)
	, mFar(10000.0f)
	, mFOV(60.0f)
	, mSize(1.0f)
	, mAspectRatio(1.0f)
	, mView(Matrix::Identity)
	, mProjection(Matrix::Identity)
	, mProjectionType(eProjectionType::Orthographic)
	, mCameraType(eCameraType::End)
{
}

Camera::~Camera()
{
}

void Camera::initialize()
{
}

void Camera::update()
{
	Assert(mRenderTargetRenderer, WCHAR_IS_NULLPTR);
	Assert(mScreenSize != Vector2::Zero, WCHAR_IS_NULLPTR);

	mRenderTargetRenderer->RegisterRenderCamera(this);
}

void Camera::lateUpdate()
{
	const Transform* const transform = GetComponent<Transform>();
	const Vector3& pos = transform->GetPosition();

	// View Translate Matrix
	mView = Matrix::Identity;
	mView *= Matrix::CreateTranslation(-pos);

	// View Rotation Matrix
	const Vector3& up = transform->GetUp();
	const Vector3& right = transform->GetRight();
	const Vector3& foward = transform->GetForward();

	Matrix viewRotate = {};

	viewRotate._11 = right.x;	viewRotate._12 = up.x;	viewRotate._13 = foward.x;
	viewRotate._21 = right.y;	viewRotate._22 = up.y;	viewRotate._23 = foward.y;
	viewRotate._31 = right.z;	viewRotate._32 = up.z;	viewRotate._33 = foward.z;

	mView *= viewRotate;

	//const Vector2 screenSize = gEngine->GetScreenSize();

	mAspectRatio = mScreenSize.x / mScreenSize.y;

	switch (mProjectionType)
	{
	case Camera::eProjectionType::Perspective:
		mProjection = Matrix::CreatePerspectiveFieldOfViewLH(Deg2Rad(mFOV), mAspectRatio, mNear, mFar);
		break;
	case Camera::eProjectionType::Orthographic:
	{
		const float OrthorGraphicRatio = mSize / 1.0f;
		const float width = mScreenSize.x * OrthorGraphicRatio;
		const float height = mScreenSize.y * OrthorGraphicRatio;

		mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
	}
	break;
	default:
		Assert(false, WCHAR_IS_INVALID_TYPE);
		break;
	}
}
