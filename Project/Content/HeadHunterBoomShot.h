#pragma once
#include "MonsterState.h"

enum class eBoomShotState
{
	None,
	TakeOut,
	Shoot,
	PutBack,
};

class HeadHunterBoomShot : public MonsterState
{
public:
	HeadHunterBoomShot();
	virtual ~HeadHunterBoomShot();
	HeadHunterBoomShot(const HeadHunterBoomShot&) = delete;
	HeadHunterBoomShot& operator=(const HeadHunterBoomShot&) = delete;

	// MonsterState을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	// MonsterState을(를) 통해 상속됨
	virtual void Initialize() override;

	int mShootCount;
	eBoomShotState mBoomShotState;
};

