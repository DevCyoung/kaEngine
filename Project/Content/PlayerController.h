#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(PlayerController);

class PlayerFSM;

class PlayerController : public ScriptComponent
{
public:
	PlayerController();
	virtual ~PlayerController();
	PlayerController(const PlayerController&) = delete;
	PlayerController& operator=(const PlayerController&) = delete;
	void SetFSM(PlayerFSM* const playerFSM) { mPlayerFSM = playerFSM; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	void idleToRun();
	void runToIdle();

	PlayerFSM* mPlayerFSM;
};
