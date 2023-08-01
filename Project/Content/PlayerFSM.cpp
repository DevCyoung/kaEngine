#include "pch.h"
#include "PlayerFSM.h"
#include "Components.h"
#include "Rect2DInterpolation.h"

PlayerFSM::PlayerFSM(GameObject* const owner)
	: mOwner(owner)
	, mRect2DInterpolation(nullptr)
	, mRigidbody2D(nullptr)
	, mAnimator2D(nullptr)
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
	, mPlayerGlobalState(new PlayerGlobalState(owner, this))
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
	SAFE_DELETE_POINTER(mPlayerGlobalState);

}

//FIXME: 모든 state Initialize 추가해줘야함
void PlayerFSM::Initialize(PlayerState* const startState)
{
	mRect2DInterpolation = mOwner->GetComponent<Rect2DInterpolation>();
	mRigidbody2D = mOwner->GetComponent<Rigidbody2D>();
	mAnimator2D = mOwner->GetComponent<Animator2D>();

	mPlayerIdleState->Initialize();
	mPlayerRunState->Initialize();
	mPlayerAttackState->Initialize();
	mPlayerRollState->Initialize();
	mPlayerCrouchState->Initialize();
	mPlayerJumpState->Initialize();
	mPlayerFallState->Initialize();
	mPlayerDoorBreakFullState->Initialize();
	mPlayerDoorState->Initialize();
	mPlayerFlipState->Initialize();
	mPlayerWallSlideState->Initialize();
	mPlayerGlobalState->Initialize();

	mCurState = startState;
	mCurState->Enter();
}

void PlayerFSM::GlobalUpdate()
{	
	if (CanChagneToAttackState())
	{
		ChangeState(mPlayerAttackState);
	}
	else if (CanChagneToJumpState())
	{
		ChangeState(mPlayerJumpState);
	}
	else if (CanChagneToRunState())
	{
		mAnimator2D->Play(L"IdleToRun", false);
		ChangeState(mPlayerRunState);
	}
	else if (CanChagneToWallSlideState())
	{
		ChangeState(mPlayerWallSlideState);
	}
	else if (CanChagneToFallState())
	{
		ChangeState(mPlayerFallState);
	}


}

void PlayerFSM::InputUpdate()
{
	mCurState->InputUpdate();
}

void PlayerFSM::Update()
{
	mCurState->Update();
}

bool PlayerFSM::CanChagneToAttackState() const
{
	return gInput->GetKeyDown(eKeyCode::LBTN) && mCurState != mPlayerAttackState;
}

bool PlayerFSM::CanChagneToFallState() const
{
	if (mCurState == mPlayerFallState || 
		mCurState == mPlayerWallSlideState || 
		mCurState == mPlayerAttackState || 
		mCurState == mPlayerFlipState)
	{
		return false;
	}

	if (mRigidbody2D->GetVelocity().y >= 0.f || mRigidbody2D->IsGround())
	{
		return false;
	}

	return true;
}

bool PlayerFSM::CanChagneToJumpState() const
{
	return gInput->GetKeyDown(eKeyCode::W) && mRect2DInterpolation->IsCollisionWallDown();
}

bool PlayerFSM::CanChagneToRunState() const
{
	if (mPlayerRunState == mCurState)
	{
		return false;
	}

	if (mPlayerIdleState != mCurState)
	{
		return false;
	}

	if (gInput->GetKey(eKeyCode::A) == false && gInput->GetKey(eKeyCode::D) == false)
	{		
		return false;
	}

	if (gInput->GetKey(eKeyCode::A) && gInput->GetKey(eKeyCode::D))
	{
		return false;
	}

	if (mRect2DInterpolation->IsCollisionWallRight() &&  gInput->GetKey(eKeyCode::D))
	{
		return false;
	}

	if (mRect2DInterpolation->IsCollisionWallLeft() && gInput->GetKey(eKeyCode::A))
	{
		return false;
	}

	if (mRect2DInterpolation->IsCollisionWallDown() == false)
	{
		return false;
	}

	return true;
}

bool PlayerFSM::CanChagneToWallSlideState() const
{	
	if (mCurState == mPlayerWallSlideState)
	{
		return false;
	}

	if (mRect2DInterpolation->IsCollisionWallDown())
	{
		return false;
	}

	Vector2 velocity = mRigidbody2D->GetVelocity();

	if (0.f < velocity.x || gInput->GetKey(eKeyCode::D))
	{
		if (mRect2DInterpolation->IsCollisionWallRight())
		{
			return true;
		}		
	}

	if (0.f > velocity.x || gInput->GetKey(eKeyCode::A))
	{
		if (mRect2DInterpolation->IsCollisionWallLeft())
		{
			return true;
		}
	}

	if (mCurState == mPlayerFlipState)
	{
		if (mRect2DInterpolation->IsCollisionWallRight())
		{
			return true;
		}
		if (mRect2DInterpolation->IsCollisionWallLeft())
		{
			return true;
		}
	}

	return false;
}
