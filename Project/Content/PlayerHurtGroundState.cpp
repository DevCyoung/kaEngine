#include "pch.h"
#include "PlayerHurtGroundState.h"
#include "Components.h"
#include "PlayerFSM.h"
#include "Rect2DInterpolation.h"

#include "PlayerFSM.h"
#include "PlayerController.h"

#include "GameManager.h"
#include "KatanaZeroSystem.h"

PlayerHurtGroundState::PlayerHurtGroundState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
	, mbInvincibility(true)
{
}

PlayerHurtGroundState::~PlayerHurtGroundState()
{
}

void PlayerHurtGroundState::InputUpdate()
{
}

void PlayerHurtGroundState::Update()
{
	if (gInput->GetKeyDown(eKeyCode::LBTN))
	{
		if (false == KatanaZeroSystem::GetInstance()->IsPlayerDamaged())
		{
			mOwner->ChangeState(mOwner->mPlayerRecoverState);
		}		
		else
		{
			GameManager::GetInstance()->GetRewindManager()->Rewind();
		}
	}
}

void PlayerHurtGroundState::Enter()
{
	mAnimator->Play(L"HurtGround", false);
}

void PlayerHurtGroundState::Exit()
{
}
