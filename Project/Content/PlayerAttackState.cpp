#include "pch.h"
#include "PlayerAttackState.h"
#include "Components.h"
#include "PlayerFSM.h"

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
	if (gInput->GetKey(eKeyCode::A) || gInput->GetKey(eKeyCode::D))
	{
		Vector3 dir = Vector3::Zero;

		if (gInput->GetKey(eKeyCode::A))
		{
			dir.x -= 1.f;
		}
		if (gInput->GetKey(eKeyCode::D))
		{
			dir.x += 1.f;
		}

		if (dir.Length() > 0.1f)
		{
			mAnimator->Play(L"IdleToRun", false);
			mOwner->ChangeState(mOwner->mPlayerRunState);
			return;
		}
	}
}

void PlayerAttackState::Enter()
{
	mAnimator->Play(L"Attack", false);
}

void PlayerAttackState::Exit()
{
}
