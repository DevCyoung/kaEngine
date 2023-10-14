#pragma once
#include "MonsterState.h"
class HeadHunterRoll : public MonsterState
{
public:
	HeadHunterRoll();
	virtual ~HeadHunterRoll();
	HeadHunterRoll(const HeadHunterRoll&) = delete;
	HeadHunterRoll& operator=(const HeadHunterRoll&) = delete;

	// MonsterState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;
};

