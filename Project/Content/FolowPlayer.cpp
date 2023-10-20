#include "pch.h"
#include "FolowPlayer.h"
#include "Components.h"
#include <Engine/EngineMath.h>
#include "CameraWall.h"

FolowPlayer::FolowPlayer()
	: ScriptComponent(eScriptComponentType::FolowPlayer)
	, mPlayerTransform(nullptr)
	, mShakeTime(0.f)
	, mbShake(false)
	, mbCollideWall{}
	, mShakeCount(0)
	, mbFolow(true)
	, mPrevPosition(Vector3::Zero)
{
}

FolowPlayer::~FolowPlayer()
{
}

void FolowPlayer::ShakeCamera()
{
	mPrevPosition = GetOwner()->GetComponent<Transform>()->GetPosition();

	mShakeTime = 0.f;
	mbShake = true;
}

void FolowPlayer::initialize()
{
	mPlayerTransform = GetOwner()->GetGameSystem()->FindGameObject(L"Player")->GetComponent<Transform>();
}

void FolowPlayer::update()
{
	if (nullptr == mPlayerTransform)
	{
		return;
	}


	const Vector3& TARGET_POS = mPlayerTransform->GetPosition();
	const Vector3& CAMERA_POS = GetOwner()->GetComponent<Transform>()->GetPosition();
	Vector3 NextPos = CAMERA_POS;

	Vector3 direction = TARGET_POS - CAMERA_POS;
	direction.z = 0.f;
	const float DISTANCE = direction.Length();

	direction.Normalize();

	if (mbCollideWall[static_cast<UINT>(eCameraWallType::Left)])
	{
		if (direction.x < 0.f)
		{
			direction.x = 0.f;
		}
	}
	if (mbCollideWall[static_cast<UINT>(eCameraWallType::Right)])
	{
		if (direction.x > 0.f)
		{
			direction.x = 0.f;
		}
	}
	if (mbCollideWall[static_cast<UINT>(eCameraWallType::Up)])
	{
		if (direction.y > 0.f)
		{
			direction.y = 0.f;
		}
	}
	if (mbCollideWall[static_cast<UINT>(eCameraWallType::Down)])
	{
		if (direction.y < 0.f)
		{
			direction.y = 0.f;
		}
	}	

	if (mbFolow)
	{
		if (DISTANCE > 50.f)
		{
			NextPos += direction * gDeltaTime * 1000.f;
		}
	}	

	//if (gInput->GetKeyDown(eKeyCode::J))
	//{
	//	ShakeCamera();
	//}

	if (mbShake)
	{
		mShakeTime += gDeltaTime;
		mShakeInterverTime += gDeltaTime;

		int power = 10;
		float interval = 0.01f;
		float shakeTime = 0.1f;

		if (mShakeInterverTime > interval)
		{
			int offsetX = helper::rand::RandInt(-power, power);
			int offsetY = helper::rand::RandInt(-power, power);

			NextPos.x += offsetX;
			NextPos.y += offsetY;
			mShakeInterverTime = 0.f;
			mShakeCount++;
		}


		/*if (mShakeTime > shakeTime)
		{
			mbShake = false;
		}*/

		if (mShakeTime > shakeTime)
		{
			mShakeCount = 0;
			mbShake = false;

			if (false == mbFolow)
			{
				NextPos = mPrevPosition;
			}
		}

	}


	/*Camera* mainCamera = GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::Main);

	Vector3 mouseWorldPos = helper::WindowScreenMouseToWorld3D(mainCamera);	
	Vector3 cameraPos = GetOwner()->GetComponent<Transform>()->GetPosition();

	Vector3 direction2 = mouseWorldPos - cameraPos;	
	NextPos.x += direction2.x  * gDeltaTime;
	NextPos.y += direction2.y  * gDeltaTime;*/



	GetOwner()->GetComponent<Transform>()->SetPosition(NextPos);
}

void FolowPlayer::fixedUpdate()
{

}


void FolowPlayer::lateUpdate()
{    //Camera* const camera = GetOwner()->GetComponent<Camera>();


}

void FolowPlayer::lastUpdate()
{

}

void FolowPlayer::onCollisionEnter(Collider2D* other)
{
	(void)other;

	GameObject* wallObject = other->GetOwner();

	if (wallObject->GetLayer() == eLayerType::CameraWall)
	{
		CameraWall* cameraWall = wallObject->GetComponent<CameraWall>();
		eCameraWallType type = cameraWall->GetCameraWallType();


		Vector3 cameraPosition = GetOwner()->GetComponent<Transform>()->GetPosition();

		Vector3 wallSize = wallObject->GetComponent<RectCollider2D>()->GetSize();
		Vector3 wallPosition = wallObject->GetComponent<Transform>()->GetPosition();
		Vector3 cameraSize = GetOwner()->GetComponent<RectCollider2D>()->GetSize();

		switch (type)
		{
		case eCameraWallType::Left:
		{
			cameraPosition.x = wallPosition.x + wallSize.x * 0.5f + cameraSize.x * 0.5f;
		}
		break;
		case eCameraWallType::Right:
			cameraPosition.x = wallPosition.x - wallSize.x * 0.5f - cameraSize.x * 0.5f;
			break;
		case eCameraWallType::Down:
			cameraPosition.y = wallPosition.y + wallSize.y * 0.5f + cameraSize.y * 0.5f;
			break;
		case eCameraWallType::Up:
			break;
		default:
			assert(false);
			break;
		}

		GetOwner()->GetComponent<Transform>()->SetPosition(cameraPosition);

		mbCollideWall[static_cast<UINT>(type)] = true;
	}	
}

void FolowPlayer::onCollisionStay(Collider2D* other)
{
	(void)other;

	//GameObject* wallObject = other->GetOwner();

	//if (wallObject->GetLayer() == eLayerType::CameraWall)
	//{
	//	CameraWall* cameraWall = wallObject->GetComponent<CameraWall>();

	//	eCameraWallType type = cameraWall->GetCameraWallType();

	//}
}

void FolowPlayer::onCollisionExit(Collider2D* other)
{
	GameObject* wallObject = other->GetOwner();

	if (wallObject->GetLayer() == eLayerType::CameraWall)
	{
		CameraWall* cameraWall = wallObject->GetComponent<CameraWall>();
		eCameraWallType type = cameraWall->GetCameraWallType();

		mbCollideWall[static_cast<UINT>(type)] = false;
	}
}
