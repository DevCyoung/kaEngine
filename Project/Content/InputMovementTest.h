#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(InputMovementTest);

class InputMovementTest : public ScriptComponent
{
public:
	InputMovementTest();
	virtual ~InputMovementTest();
	InputMovementTest(const InputMovementTest&) = delete;
	InputMovementTest& operator=(const InputMovementTest&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
