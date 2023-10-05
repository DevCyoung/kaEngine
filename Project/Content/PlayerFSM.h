#pragma once
#include "FiniteStateMachine.h"

#include "PlayerIdleState.h"	
#include "PlayerRunState.h"
#include "PlayerAttackState.h"
#include "PlayerRollState.h"
#include "PlayerCrouchState.h"
#include "PlayerController.h"
#include "PlayerJumpState.h"
#include "PlayerFallState.h"
#include "PlayerDoorBreakFullState.h"
#include "PlayerDoorState.h"
#include "PlayerFlipState.h"
#include "PlayerWallSlideState.h"
#include "PlayerGlobalState.h"
#include "PlayerRecoverState.h"
#include "PlayerHurtGroundState.h"
#include "PlayerHurtState.h"

class GameObject;

class PlayerFSM : public FiniteStateMachine
{
public:
	PlayerFSM(GameObject* const Owner);
	virtual ~PlayerFSM();

	// FiniteStateMachine을(를) 통해 상속됨

	void Initialize(PlayerState* const startState);

	virtual void GlobalUpdate() override final;
	virtual void InputUpdate() override final;
	virtual void Update() override final;

	const Vector3& GetVelocity() const { return mVelocity; };
	Vector3 SetVelocity(const Vector3& velocity) { mVelocity = velocity; };

public:
	bool CanChagneToAttackState() const;
	bool CanChagneToFallState() const;
	bool CanChagneToJumpState() const;
	bool CanChagneToRunState() const;
	bool CanChagneToWallSlideState() const;


private:
	GameObject* mOwner;

	Rect2DInterpolation* mRect2DInterpolation;
	Rigidbody2D* mRigidbody2D;
	Animator2D* mAnimator2D;

	Vector3 mVelocity;

public:
	PlayerIdleState* mPlayerIdleState;
	PlayerRunState* mPlayerRunState;
	PlayerAttackState* mPlayerAttackState;
	PlayerRollState* mPlayerRollState;
	PlayerCrouchState* mPlayerCrouchState;
	PlayerJumpState* mPlayerJumpState;
	PlayerFallState* mPlayerFallState;
	PlayerDoorBreakFullState* mPlayerDoorBreakFullState;
	PlayerDoorState* mPlayerDoorState;
	PlayerFlipState* mPlayerFlipState;
	PlayerWallSlideState* mPlayerWallSlideState;
	PlayerGlobalState* mPlayerGlobalState;
	PlayerRecoverState* mPlayerRecoverState;
	PlayerHurtGroundState* mPlayerHurtGroundState;
	PlayerHurtState* mPlayerHurtState;
};
