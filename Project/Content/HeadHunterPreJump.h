#pragma once
#include "MonsterState.h"

enum class ePreJumpState
{
	None,
	PreJump,
	Jump,
};

class HeadHunterPreJump : public MonsterState
{
public:
	HeadHunterPreJump();
	virtual ~HeadHunterPreJump();
	HeadHunterPreJump(const HeadHunterPreJump&) = delete;
	HeadHunterPreJump& operator=(const HeadHunterPreJump&) = delete;

	virtual void Initialize() override;
	// MonsterState을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	ePreJumpState mState;
};

