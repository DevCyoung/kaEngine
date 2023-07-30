#include "pch.h"
#include "PlayerRollState.h"
#include "PlayerFSM.h"
#include "Components.h"

PlayerRollState::PlayerRollState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
	, time(0.f)
	, prevDirX(0.f)
{
}

PlayerRollState::~PlayerRollState()
{
}

void PlayerRollState::InputUpdate()
{
}

void PlayerRollState::Update()
{		
	time += gDeltaTime;
	mOwner->mPlayerGlobalState->InputFlip();

	Vector2 right = Vector2::Right * prevDirX;

	mRigidbody->SetVelocity(right * 500.f);

	if (time > 0.30f)
	{
		mAnimator->Play(L"RunToIdle", false);
		mOwner->ChangeState(mOwner->mPlayerIdleState);
		mRigidbody->SetVelocity(right * 10.f);
		return;
	}
}

void PlayerRollState::Enter()
{
	mAnimator->Play(L"Roll", false);
	time = 0.f;

	Vector2 dir = mOwner->mPlayerGlobalState->GetInputDirectionX();
	prevDirX = dir.x;
}

void PlayerRollState::Exit()
{
}
