#pragma once
#include "Components.h"

class MonsterFSM;


class MonsterState
{
friend class MonsterFSM;

public:
	MonsterState();
	virtual ~MonsterState();
	MonsterState(const MonsterState&) = delete;
	MonsterState& operator=(const MonsterState&) = delete;
	
	virtual void Initialize();
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	int GetStateType() const { return mType; }
	MonsterFSM* GetMonsterFSM() const { return mMonsterFSM; }

private:
	MonsterFSM* mMonsterFSM;
	int mType;

protected:
	Transform* mTransform;
	Animator2D* mAnimator2D;
	Rigidbody2D* mRigidbody2D;
	GameObject* mGameObject;
	
};

