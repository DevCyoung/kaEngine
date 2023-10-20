#include "pch.h"
#include "PlayerRecoverState.h"
#include "Components.h"
#include "PlayerFSM.h"
#include "Rect2DInterpolation.h"


PlayerRecoverState::PlayerRecoverState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerRecoverState::~PlayerRecoverState()
{
}

void PlayerRecoverState::InputUpdate()
{
}

void PlayerRecoverState::Update()
{
	if (mAnimator->GetCurAnimationOrNull()->IsFinished())
	{
		mAnimator->Play(L"Idle", false);
		mOwner->ChangeState(mOwner->mPlayerIdleState);
		mGameObject->GetComponent<PlayerController>()->SetControl(true);
	}
}

void PlayerRecoverState::Enter()
{
	mAnimator->Play(L"HurtRecover", false);
}

void PlayerRecoverState::Exit()
{
}
