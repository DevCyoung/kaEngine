#include "pch.h"
#include "PlayerCrouchState.h"
#include "Components.h"
#include "PlayerFSM.h"


PlayerCrouchState::PlayerCrouchState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerCrouchState::~PlayerCrouchState()
{
}

void PlayerCrouchState::InputUpdate()
{
}

void PlayerCrouchState::Update()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();

	if (gInput->GetKey(eKeyCode::S) == false)
	{
		animator->Play(L"PostCrouch", false);
		mOwner->ChangeState(mOwner->mPlayerIdleState);
		return;
	}


	if (mOwner->mPlayerGlobalState->IsRollInput())
	{
		mOwner->ChangeState(mOwner->mPlayerRollState);
	}

}

void PlayerCrouchState::Enter()
{
}

void PlayerCrouchState::Exit()
{
}
