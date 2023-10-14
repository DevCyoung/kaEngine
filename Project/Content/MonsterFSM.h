#pragma once

#include "MonsterState.h"
#define MAX_MONSTER_STATES 256

class MonsterFSM
{
public:
	MonsterFSM(GameObject* owner);
	virtual ~MonsterFSM();
	MonsterFSM(const MonsterFSM&) = delete;
	MonsterFSM& operator=(const MonsterFSM&) = delete;

	virtual void Initialize(int idx);
	virtual void GlobalUpdate();	
	virtual void Update();

	void AddState(int idx, MonsterState* state);
	void ChangeState(int idx);

	GameObject* GetOwner() const { return mOwner; }


private:
	MonsterState* mMonsterStates[MAX_MONSTER_STATES];
	MonsterState* mRegisterEnterState;
	MonsterState* mCurrentState;
	GameObject* mOwner;
};

