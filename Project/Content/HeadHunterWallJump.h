#pragma once
#include "MonsterState.h"

enum class eWallJumpState
{
	None,
	Idle,
	Jump,
	Land,
};

class HeadHunterWallJump : public MonsterState
{
public:
	HeadHunterWallJump();
	virtual ~HeadHunterWallJump();
	HeadHunterWallJump(const HeadHunterWallJump&) = delete;
	HeadHunterWallJump& operator=(const HeadHunterWallJump&) = delete;

	virtual void Initialize() override;

	// MonsterState을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	eWallJumpState mWallJumpState;
	float mJumpTime;
	float mShotTime;
	int mBulletCount;
};

