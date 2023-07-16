#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(PlayerMovementTest);

class PlayerMovementTest : public ScriptComponent
{
public:
	PlayerMovementTest();
	virtual ~PlayerMovementTest();
	PlayerMovementTest(const PlayerMovementTest&) = delete;
	PlayerMovementTest& operator=(const PlayerMovementTest&) = delete;

	bool mbRight;
	float angle;


private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
