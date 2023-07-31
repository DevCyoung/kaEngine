#include "pch.h"
#include "PlayerFlipState.h"
#include "Components.h"
#include "PlayerFSM.h"
#include "Rect2DInterpolation.h"

PlayerFlipState::PlayerFlipState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
	, time(0.f)
{
}

PlayerFlipState::~PlayerFlipState()
{
}

void PlayerFlipState::InputUpdate()
{
}

void PlayerFlipState::Update()
{
	if (mInter->IsCollisionWallDown())
	{
		mAnimator->Play(L"RunToIdle", false);
		mOwner->ChangeState(mOwner->mPlayerIdleState);
		mOwner->ChangeState(mOwner->mPlayerIdleState);
		
	}

	if (time > 0.3f)
	{
		return;
	}	

	time += gDeltaTime;

	if (time > 0.3f)
	{
		Vector2 velocity = mRigidbody->GetVelocity();
		velocity.x *= 0.4f;
		mRigidbody->SetVelocity(velocity);
	}
}

void PlayerFlipState::Enter()
{

	Vector3 right = mTransform->GetRight();
	Vector2 dir = Vector2( -right.x * 1.5f, 1.f );

	mRigidbody->SetVelocity(dir * 338.f);

	mAnimator->Play(L"Flip", false);

	time = 0.f;
}

void PlayerFlipState::Exit()
{
}
