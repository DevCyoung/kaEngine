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
	//if (gInput->GetKey(eKeyCode::A) || gInput->GetKey(eKeyCode::D))
	//{
	//	Vector3 dir = Vector3::Zero;
	//
	//	if (gInput->GetKey(eKeyCode::A))
	//	{
	//		dir.x -= 1.f;
	//	}
	//	if (gInput->GetKey(eKeyCode::D))
	//	{
	//		dir.x += 1.f;
	//	}
	//
	//	if (dir.Length() > 0.1f)
	//	{
	//		mAnimator->Play(L"IdleToRun", false);
	//		mOwner->ChangeState(mOwner->mPlayerRunState);
	//		return;
	//	}
	//}


	if (gInput->GetKey(eKeyCode::S))
	{
		mAnimator->Play(L"PreCrouch", false);
		mOwner->ChangeState(mOwner->mPlayerCrouchState);
		return;
	}
}

void PlayerIdleState::Enter()
{
}

void PlayerIdleState::Exit()
{
}
