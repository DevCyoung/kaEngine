#pragma once
#include "MonsterState.h"

enum class eSweepState
{
	None,
	Sweep,
	In,
	Out,
};

class HeadHunterSweep : public MonsterState
{
public:
	HeadHunterSweep();
	virtual ~HeadHunterSweep();
	HeadHunterSweep(const HeadHunterSweep&) = delete;
	HeadHunterSweep& operator=(const HeadHunterSweep&) = delete;

	// MonsterState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	void SweepIn();

	void Shot();

	eSweepState mSweepState;
	GameObject* mSweepLazer;
	bool mbLeft;
	int mSweepCount;
};

