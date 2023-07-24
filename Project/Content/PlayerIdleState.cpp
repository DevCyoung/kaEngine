#include "pch.h"
#include "PlayerIdleState.h"
#include "PlayerFSM.h"
#include "Components.h"

PlayerIdleState::PlayerIdleState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{

}

PlayerIdleState::~PlayerIdleState()
{

}

void PlayerIdleState::InputUpdate()
{
}

void PlayerIdleState::Update()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();
	//
	//Run
	if (gInput->GetKey(eKeyCode::LEFT) || gInput->GetKey(eKeyCode::RIGHT))
	{
		Vector3 dir = Vector3::Zero;

		if (gInput->GetKey(eKeyCode::LEFT))
		{
			dir.x -= 1.f;
		}
		if (gInput->GetKey(eKeyCode::RIGHT))
		{
			dir.x += 1.f;
		}

		if (dir.Length() > 0.1f)
		{
			animator->Play(L"IdleToRun", false);
			mOwner->ChangeState(mOwner->mPlayerRunState);
			return;
		}
	}


	if (gInput->GetKey(eKeyCode::DOWN))
	{
		animator->Play(L"PreCrouch", false);
		mOwner->ChangeState(mOwner->mPlayerCrouchState);
		return;
	}
}

void PlayerIdleState::Enter()
{
	//Animator2D* const animator = mGameObject->GetComponent<Animator2D>();	
	//animator->Play(L"RunToIdle", false);
}

void PlayerIdleState::Exit()
{
}
