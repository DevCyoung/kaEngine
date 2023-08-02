#include "pch.h"
#include "PlayerJumpState.h"
#include "Components.h"
#include "PlayerFSM.h"
#include "Rect2DInterpolation.h"

PlayerJumpState::PlayerJumpState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::InputUpdate()
{
}

void PlayerJumpState::Update()
{
	Vector2 dir = mOwner->mPlayerGlobalState->GetInputDirectionX();
	Vector2 velocity = mRigidbody->GetVelocity();
	mOwner->mPlayerGlobalState->InputFlip();

	if (mInter->IsCollisionSlop())
	{
		velocity.x = 0.f;
		dir.x = 0.f;
	}
	else if (velocity.Length() >= 250.f)
	{
		velocity.x = 250.f * dir.x;
	}


	mRigidbody->SetVelocity(velocity);

	//if (mInter->IsCollisionWallLeft())
	//{
	//	if (gInput->GetKey(eKeyCode::A))
	//	{
	//		mAnimator->Play(L"WallSlide", true);
	//		mOwner->ChangeState(mOwner->mPlayerWallSlideState);
	//	}
	//}
	//else if (mInter->IsCollisionWallRight())
	//{
	//	if (gInput->GetKey(eKeyCode::D))
	//	{
	//		mAnimator->Play(L"WallSlide", true);
	//		mOwner->ChangeState(mOwner->mPlayerWallSlideState);
	//	}
	//}

	//Enter
	if (mInter->IsCollisionWallDown() && velocity.y <= 0.f)
	{
		mAnimator->Play(L"RunToIdle", false);
		mOwner->ChangeState(mOwner->mPlayerIdleState);
		return;
	}

}

void PlayerJumpState::Enter()
{
	Vector2 velocity = mRigidbody->GetVelocity();
	velocity.y = Vector2::Up.y * 550.f;

	if (mInter->IsCollisionSlop())
	{
		velocity.x = 0.f;		
	}
	mRigidbody->SetVelocity(velocity);

	Vector3 pos = mTransform->GetPosition();
	pos.y += 8.f;
	mTransform->SetPosition(pos);

	mAnimator->Play(L"Jump", true);

}

void PlayerJumpState::Exit()
{
}

