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
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();

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
}

void PlayerAttackState::Enter()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();

	animator->Play(L"Attack", false);	
}

void PlayerAttackState::Exit()
{
}
