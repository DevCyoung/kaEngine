#include "pch.h"
#include "PlayerAttackState.h"
#include "Components.h"
#include "PlayerFSM.h"

#include <Engine/GameObject.h>
#include <Engine/EngineMath.h>
#include <Engine/GameSystem.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>
#include "Rect2DInterpolation.h"
#include "PlayerController.h"

PlayerAttackState::PlayerAttackState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerAttackState::~PlayerAttackState()
{
}

void PlayerAttackState::InputUpdate()
{
}

void PlayerAttackState::Update()
{
	//if (mOwner->mPlayerGlobalState->IsStop())
	//{
	//	mOwner->mPlayerGlobalState->RunToIdle();
}
	//}

void PlayerAttackState::Enter()
{

	mAnimator->Play(L"Attack", false);

	RenderTargetRenderer* render = mGameObject->GetGameSystem()->GetRenderTargetRenderer();
	Camera* const  camera = render->GetRegisteredRenderCamera(eCameraPriorityType::Main);

	Vector3 pos = helper::WindowScreenMouseToWorld3D(camera);

	Vector3 dir = pos - mGameObject->GetComponent<Transform>()->GetPosition();

	dir.z = 0.f;
	dir.Normalize();
	dir.x *= 0.6f;
	

	if (mInter->IsCollisionWallFloor())
	{
		if (dir.y <= 0.2f)
		{
			dir.y = 0.2f;
			//dir.x *= 0.6f;
		}
	}

	Vector2 dir2 = Vector2(dir.x, dir.y);

	dir2.x *= 650.f;
	dir2.y *= 750.f;

	mRigidbody->SetVelocity(dir2);

	if (dir2.x < 0)
	{
		mTransform->SetRotation(0.f, 180.f, 0.f);
	}
	else if (dir2.x > 0)
	{
		mTransform->SetRotation(0.f, 0.f, 0.f);
	}

	GameObject* slash =  mGameObject->GetComponent<PlayerController>()->GetSlash();
	slash->GetComponent<Transform>()->SetPosition(Vector3::Zero);

	slash->GetComponent<Animator2D>()->Play(L"Slash", false);

	//dir -> Right

	dir = pos - mGameObject->GetComponent<Transform>()->GetPosition();

	float deg = Rad2Deg(atan2(dir.y, dir.x));
	if (dir.x < 0.f)
	{
		deg = 180 - deg;
	}

	slash->GetComponent<Transform>()->SetRotation(0.f, 0.f, deg);


	Vector3 mpos = mTransform->GetPosition();
	mpos.y += 2.1f;
	mTransform->SetPosition(mpos);
}

void PlayerAttackState::Exit()
{
	//GameObject* slash = mGameObject->GetComponent<PlayerController>()->GetSlash();
	//slash->GetComponent<Transform>()->SetPosition(100000.f, 100000.f, 100000.f);
}


