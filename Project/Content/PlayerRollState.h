#pragma once
#include "PlayerState.h"

class PlayerRollState : public PlayerState
{
public:
	PlayerRollState(GameObject* const gameObject, PlayerFSM* const owner);
	virtual ~PlayerRollState();

	// PlayerState을(를) 통해 상속됨
	virtual void InputUpdate() override final;
	virtual void Update() override final;

	virtual void Enter() override;
	virtual void Exit()  override;
};

