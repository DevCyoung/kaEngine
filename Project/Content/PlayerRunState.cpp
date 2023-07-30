#include "pch.h"
#include "PlayerRunState.h"
#include "PlayerFSM.h"
#include "Components.h"
#include "Rect2DInterpolation.h"
#include <Engine/EngineMath.h>

PlayerRunState::PlayerRunState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerRunState::~PlayerRunState()
{
}

void PlayerRunState::InputUpdate()
{
}

void PlayerRunState::Update()
{
	const Vector2 dir = mOwner->mPlayerGlobalState->GetInputDirectionX();

	Vector2 right = Vector2::Right;

	mOwner->mPlayerGlobalState->InputFlip();

	if (mInter->IsCollisionSlop())
	{
		right.x = Deg2Rad(45.f);
	}

	if (abs(mRigidbody->GetVelocity().x) < 400.f)
	{
		mRigidbody->AddForce(right * dir.x * 4000.f);
	}
	else if (gInput->GetKeyDown(eKeyCode::A) || gInput->GetKeyDown(eKeyCode::D))
	{
		mRigidbody->SetVelocity(right * dir.x * 400.f);
	}

	if (mOwner->mPlayerGlobalState->IsRollInput())
	{
		mOwner->ChangeState(mOwner->mPlayerRollState);
	}
	else if (!mOwner->mPlayerGlobalState->IsInputMoveKey() || dir.x == 0.f)
	{
		mOwner->mPlayerGlobalState->RunToIdle();
	}
}

void PlayerRunState::Enter()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();

	animator->Play(L"IdleToRun", false);
}

void PlayerRunState::Exit()
{
}
