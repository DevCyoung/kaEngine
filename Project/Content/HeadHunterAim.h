#pragma once
#include "MonsterState.h"

enum class eAimState
{
	None,
	TakeOut,
	PutBack,
	Aim,
	LockOn,
	Shoot,	
};

class HeadHunterAim :   public MonsterState
{
public:
	HeadHunterAim();
	virtual ~HeadHunterAim();
	HeadHunterAim(const HeadHunterAim&) = delete;
	HeadHunterAim& operator=(const HeadHunterAim&) = delete;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	void aim();
	void rifleShoot();
	void lockOnShoot();
	void EnterAim();

	int mShootCount;

	int mFrameIdx;

	float mShootDelay;
	eAimState mAimState;
};


