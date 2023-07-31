#include "pch.h"
#include "PlayerWallSlideState.h"
#include "Components.h"
#include "PlayerFSM.h"
#include "Rect2DInterpolation.h"

PlayerWallSlideState::PlayerWallSlideState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
	, gravityScale(0.f)
	, oriGravityScale(0.f)
{
}

PlayerWallSlideState::~PlayerWallSlideState()
{
}


void PlayerWallSlideState::Initialize()
{
	PlayerState::Initialize();	

	oriGravityScale = mRigidbody->GetGravityScale();
	oriGravityLimit = mRigidbody->GetGravityVelocityLimit();
}


void PlayerWallSlideState::InputUpdate()
{
}

void PlayerWallSlideState::Update()
{
	if (mInter->IsCollisionWallLeft())
	{
		if (gInput->GetKey(eKeyCode::D))
		{			
			mOwner->ChangeState(mOwner->mPlayerFallState);
		}
		else if (gInput->GetKeyDown(eKeyCode::W))
		{
			mOwner->ChangeState(mOwner->mPlayerFlipState);			
			mOwner->mPlayerFlipState->prevDir = 1;
		}

	}
	else if (mInter->IsCollisionWallRight())
	{
		if (gInput->GetKey(eKeyCode::A))
		{				
			mOwner->ChangeState(mOwner->mPlayerFallState);			
		}
		else if (gInput->GetKeyDown(eKeyCode::W))
		{
			mOwner->ChangeState(mOwner->mPlayerFlipState);
			mOwner->mPlayerFlipState->prevDir = -1;
		}
	}
	if (mInter->IsCollisionWallDown())
	{
		mAnimator->Play(L"RunToIdle", false);
		mOwner->ChangeState(mOwner->mPlayerIdleState);		
	}	
}

void PlayerWallSlideState::Enter()
{	
	mAnimator->Play(L"WallSlide", false);	
	mRigidbody->SetGravityAccel(oriGravityScale * 0.5f);	
}

void PlayerWallSlideState::Exit()
{	
	mRigidbody->SetGravityAccel(oriGravityScale);	
}

