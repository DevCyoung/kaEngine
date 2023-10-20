#include "pch.h"
#include "PlayerFallState.h"
#include "Components.h"
#include "PlayerFSM.h"
#include "Rect2DInterpolation.h"
#include <Engine/EngineMath.h>
#include "GameManager.h"

PlayerFallState::PlayerFallState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerFallState::~PlayerFallState()
{
}

void PlayerFallState::InputUpdate()
{
}

void PlayerFallState::Update()
{
	//Vector2 dir = mOwner->mPlayerGlobalState->GetInputDirectionX();
	//Vector2 velocity = mRigidbody->GetVelocity();
	//
	//velocity.x = 250.f * dir.x;
	//

	const Vector2 dir = mOwner->mPlayerGlobalState->GetInputDirectionX();

	Vector2 right = Vector2::Right;

	mOwner->mPlayerGlobalState->InputFlip();

	if (mInter->IsCollisionWallSlop())
	{
		right.x = Deg2Rad(45.f);
	}

	if (abs(mRigidbody->GetVelocity().x) < 400.f)
	{
		mRigidbody->AddForce(right * dir.x * 700.f);
	}

	if (mInter->IsCollisionWallFloor() || mInter->IsCollisionWallSlop())
	{
		mAnimator->Play(L"RunToIdle", false);
		mOwner->ChangeState(mOwner->mPlayerIdleState);

		gSoundManager->Play(eResAudioClip::playerLand, 0.3f);
		Vector3 position =  mTransform->GetPosition();
		position.y -= 22.f;
		gEffectManager->Shot(L"LandCloud", position);

		return;
	}

	//else if (mInter->IsCollisionSlop())
	//{
	//	velocity.x /= 10.f;
	//	dir.x = 0.f;
	//}
	//else if (abs(velocity.x) >= 250.f)
	//{
	//	
	//}
	//
	//
	//
	////mRigidbody->AddForce(Vector2::Right * dir.x * 3888.f);
	//mRigidbody->SetVelocity(velocity);

}

void PlayerFallState::Enter()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();
	animator->Play(L"Fall", true);
}

void PlayerFallState::Exit()
{
}
