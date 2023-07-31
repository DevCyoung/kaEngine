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


private:
	GameObject* mOwner;
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
};
