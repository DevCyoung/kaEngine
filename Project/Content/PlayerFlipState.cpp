#include "pch.h"
#include "PlayerFlipState.h"
#include "Components.h"
#include "PlayerFSM.h"
#include "Rect2DInterpolation.h"
#include "GameManager.h"
#include <Engine/EngineMath.h>

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
	if (mInter->IsCollisionWallFloor())
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
	Vector2 right = Vector2::Right;

	if (mInter->IsCollisionWallRight())
	{
		right = Vector2::Left;
	}

	if (right.x < 0)
	{
		mTransform->SetRotation(0.f, 180.f, 0.f);
	}
	else if (right.x > 0)
	{
		mTransform->SetRotation(0.f, 0.f, 0.f);
	}

	Vector2 dir = Vector2( right.x * 1.7f, 1.7f );

	mRigidbody->SetVelocity(dir * 338.f);

	mAnimator->Play(L"Flip", false);

	time = 0.f;

	int rand = helper::rand::RandInt(0, 10000) % 3;	

	if (rand == 0)
	{
		gSoundManager->Play(eResAudioClip::playerWallKick1, 0.5f);
	}
	else if (rand == 1)
	{
		gSoundManager->Play(eResAudioClip::playerWallKick2, 0.5f);
	}
	else
	{
		gSoundManager->Play(eResAudioClip::playerWallKick3, 0.5f);
	}
}

void PlayerFlipState::Exit()
{
}
