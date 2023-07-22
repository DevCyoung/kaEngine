#include "pch.h"
#include "PlayerFSM.h"
#include "Components.h"

PlayerFSM::PlayerFSM(GameObject* const owner)
	: mOwner(owner)
	, mVelocity(Vector3::Zero)
	, mPlayerIdleState(new PlayerIdleState(owner, this))
	, mPlayerRunState(new PlayerRunState(owner, this))
	, mPlayerAttackState(new PlayerAttackState(owner, this))
	, mPlayerRollState(new PlayerRollState(owner, this))
	, mPlayerCrouchState(new PlayerCrouchState(owner, this))
	, mPlayerJumpState(new PlayerJumpState(owner, this))
	, mPlayerFallState(new PlayerFallState(owner, this))
	, mPlayerDoorBreakFullState(new PlayerDoorBreakFullState(owner, this))
	, mPlayerDoorState(new PlayerDoorState(owner, this))
	, mPlayerFlipState(new PlayerFlipState(owner, this))
	, mPlayerWallSlideState(new PlayerWallSlideState(owner, this))
{
	mCurState = mPlayerIdleState;	
}

PlayerFSM::~PlayerFSM()
{
	SAFE_DELETE_POINTER(mPlayerIdleState);
	SAFE_DELETE_POINTER(mPlayerRunState);
	SAFE_DELETE_POINTER(mPlayerAttackState);
	SAFE_DELETE_POINTER(mPlayerRollState);
	SAFE_DELETE_POINTER(mPlayerCrouchState);
	SAFE_DELETE_POINTER(mPlayerJumpState);
	SAFE_DELETE_POINTER(mPlayerFallState);
	SAFE_DELETE_POINTER(mPlayerDoorBreakFullState);
	SAFE_DELETE_POINTER(mPlayerDoorState);
	SAFE_DELETE_POINTER(mPlayerFlipState);
	SAFE_DELETE_POINTER(mPlayerWallSlideState);

}

void PlayerFSM::Initialize(PlayerState* const startState)
{
	mCurState = startState;	
	mCurState->Enter();
}

void PlayerFSM::GlobalUpdate()
{	
	if (gInput->GetKeyDown(eKeyCode::LBTN))
	{
		ChangeState(mPlayerAttackState);		
	}
	else if (gInput->GetKeyDown(eKeyCode::I))
	{
		ChangeState(mPlayerFallState);
	}
	else if (gInput->GetKeyDown(eKeyCode::O))
	{
		ChangeState(mPlayerJumpState);
	}
	else if (gInput->GetKeyDown(eKeyCode::P))
	{
		ChangeState(mPlayerFlipState);
	}
	else if (gInput->GetKeyDown(eKeyCode::Q))
	{
		ChangeState(mPlayerDoorBreakFullState);
	}
	else if (gInput->GetKeyDown(eKeyCode::U))
	{
		ChangeState(mPlayerWallSlideState);
	}
	else if (gInput->GetKeyDown(eKeyCode::Y))
	{
		ChangeState(mPlayerDoorBreakFullState);
	}



}

void PlayerFSM::InputUpdate()
{
	mCurState->InputUpdate();
}

void PlayerFSM::Update()
{
	mCurState->Update();

	//Transform* const transform = mOwner->GetComponent<Transform>();

	//if (mVelocity.x < 0)
	//{
	//	transform->SetRotation(0.f, 180.f, 0.f);
	//}
	//else
	//{
	//	transform->SetRotation(0.f, 0.f, 0.f);
	//}
}
