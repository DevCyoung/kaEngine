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
	, mRenderTargetSize(Vector2::Zero)
	, mLayerMask(0XFFFFFFFF)
	, mNear(1.0f)
	, mFar(10000.0f)
	, mFOV(60.0f)
	, mSize(1.0f)
	, mAspectRatio(1.0f)
	, mView(Matrix::Identity)
	, mProjection(Matrix::Identity)
	, mProjectionType(eCameraProjectionType::Orthographic)
	, mCameraType(eCameraPriorityType::End)
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
	Assert(mRenderTargetSize != Vector2::Zero, WCHAR_IS_NULLPTR);

	mRenderTargetRenderer->registerRenderCamera(this);
}

void Camera::lateUpdate()
{
	const Transform* const P_TRANSFORM = GetComponent<Transform>();
	const Vector3& POSITION = P_TRANSFORM->GetPosition();

	// View Translate Matrix
	mView = Matrix::Identity;
	mView *= Matrix::CreateTranslation(-POSITION);

	// View Rotation Matrix
	const Vector3& UP = P_TRANSFORM->GetUp();
	const Vector3& RIGHT = P_TRANSFORM->GetRight();
	const Vector3& FORWARD = P_TRANSFORM->GetForward();

	Matrix viewRotate = {};

	viewRotate._11 = RIGHT.x;	viewRotate._12 = UP.x;	viewRotate._13 = FORWARD.x;
	viewRotate._21 = RIGHT.y;	viewRotate._22 = UP.y;	viewRotate._23 = FORWARD.y;
	viewRotate._31 = RIGHT.z;	viewRotate._32 = UP.z;	viewRotate._33 = FORWARD.z;

	mView *= viewRotate;

	//const Vector2 screenSize = gEngine->GetScreenSize();

	mAspectRatio = mRenderTargetSize.x / mRenderTargetSize.y;

	switch (mProjectionType)
	{
	case eCameraProjectionType::Perspective:
		mProjection = Matrix::CreatePerspectiveFieldOfViewLH(Deg2Rad(mFOV), mAspectRatio, mNear, mFar);
		break;
	case eCameraProjectionType::Orthographic:
	{
		const float ORTHOGRAPHIC_RATIO = mSize / 1.0f;
		const float WIDTH = mRenderTargetSize.x * ORTHOGRAPHIC_RATIO;
		const float HEIGHT = mRenderTargetSize.y * ORTHOGRAPHIC_RATIO;

		mProjection = Matrix::CreateOrthographicLH(WIDTH, HEIGHT, mNear, mFar);
	}
	break;
	default:
		Assert(false, WCHAR_IS_INVALID_TYPE);
		break;
	}
}
