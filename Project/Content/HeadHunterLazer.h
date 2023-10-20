#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(HeadHunterLazer);

enum class eLazerState
{
	None,
	Shot,
	LockOn,

	InAndOutLockOn,
	InAndOut_IN,
	InAndOut_OUT,
};

class HeadHunterLazer : public ScriptComponent
{
public:
	HeadHunterLazer();
	virtual ~HeadHunterLazer();
	HeadHunterLazer(const HeadHunterLazer&) = delete;
	HeadHunterLazer& operator=(const HeadHunterLazer&) = delete;

	void Shot();
	void LockOnShot();
	void TurnOnLazer() { mbLazerOn = true; }
	void TurnOffLazer() { mbLazerOn = false; }
	void Shot(eLazerState state);

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	
	
	bool mbShoot;
	bool mbLazerOn;
	float mInTime;
	int mUpdateCount;
	eLazerState mState;
};
