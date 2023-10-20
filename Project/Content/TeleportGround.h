#pragma once
#include "MonsterState.h"

enum class eTeleportGroundState
{
	None,
	In,
	Out,
	WallIn,
	WallJump,
};

class TeleportGround : public MonsterState
{
public:
	TeleportGround();
	virtual ~TeleportGround();
	TeleportGround(const TeleportGround&) = delete;
	TeleportGround& operator=(const TeleportGround&) = delete;

	// MonsterState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	void Shot();

	eTeleportGroundState mTelportGroundState;
};

