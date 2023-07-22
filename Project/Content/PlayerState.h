#pragma once
#include "FSMState.h"

class GameObject;
class PlayerFSM;

class PlayerState : public FSMState
{
public:
	PlayerState(GameObject* const gameObject, PlayerFSM* const owner);

	virtual ~PlayerState() {};
	virtual void InputUpdate() = 0;
	virtual void Update() = 0 ;
	virtual void Enter() override {};
	virtual void Exit()  override {};

protected:
	GameObject* mGameObject;
	PlayerFSM* mOwner;
};

