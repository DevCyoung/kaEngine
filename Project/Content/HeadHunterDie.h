#pragma once
#include "MonsterState.h"

enum class eHeadHunterDieState
{
	Idle,
	Die,
	End,
	NextScene,
};
class HeadHunterDie : public MonsterState
{
public:
	HeadHunterDie();
	virtual ~HeadHunterDie();
	HeadHunterDie(const HeadHunterDie&) = delete;
	HeadHunterDie& operator=(const HeadHunterDie&) = delete;

	// MonsterState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	float mEndTime;
	eHeadHunterDieState mState;
};

