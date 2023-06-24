#include "pch.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Engine.h"

namespace engine
{
	Camera::Camera()
		: Component(eComponentType::Camera)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mFOV(60.0f)
		, mSize(5.0f)
		, mAspectRatio(1.0f)
		, mView(Matrix::Identity)
		, mProjection(Matrix::Identity)
		, mProjectionType(eProjectionType::Orthographic)
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
	}

	void Camera::lateUpdate()
	{
	Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		// View Translate Matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);

		// View Rotation Matrix
		Vector3 up = tr->GetUp();
		Vector3 right = tr->GetRight();
		Vector3 foward = tr->GetForward();

		Matrix viewRotate;
		viewRotate._11 = right.x;	viewRotate._12 = up.x;	viewRotate._13 = foward.x;
		viewRotate._21 = right.y;	viewRotate._22 = up.y;	viewRotate._23 = foward.y;
		viewRotate._31 = right.z;	viewRotate._32 = up.z;	viewRotate._33 = foward.z;
		mView *= viewRotate;


		
		float width = static_cast<float>(gEngine->GetScreenWidth());
		float height = static_cast<float>(gEngine->GetScreenHeight());

		mAspectRatio = width / height;

		if (mProjectionType == eProjectionType::Orthographic)
		{
			float OrthorGraphicRatio = mSize / 1000.0f;
			width *= OrthorGraphicRatio;
			height *= OrthorGraphicRatio;

			mProjection = math::Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}
		else
		{
			mProjection = math::Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
		}	

	}

	void Camera::render()
	{
	}
}