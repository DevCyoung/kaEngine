#pragma once
#include "MonsterState.h"
class HeadHunterIdle : public MonsterState
{
public:
	HeadHunterIdle();
	virtual ~HeadHunterIdle();
	HeadHunterIdle(const HeadHunterIdle&) = delete;
	HeadHunterIdle& operator=(const HeadHunterIdle&) = delete;

	// MonsterState을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	// MonsterState을(를) 통해 상속됨
	virtual void Initialize() override;

	int prevRand;
};

