#pragma once
#include "PlayerState.h"
class PlayerGlobalState : public PlayerState
{
public:
	PlayerGlobalState(GameObject* const gameObject, PlayerFSM* const owner);
	virtual ~PlayerGlobalState();

	// PlayerState을(를) 통해 상속됨
	virtual void InputUpdate() override final;
	virtual void Update() override final;

	virtual void Enter() override;
	virtual void Exit()  override;


public:
	void RunToIdle();
	bool IsStop();
	bool IsInputMoveKey();
	bool IsRollInput();
	void InputFlip();
	Vector2 GetInputDirectionX();
};

