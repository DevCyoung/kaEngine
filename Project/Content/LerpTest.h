#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(LerpTest);

class LerpTest : public ScriptComponent
{
public:
	LerpTest();
	virtual ~LerpTest();
	LerpTest(const LerpTest&) = delete;
	LerpTest& operator=(const LerpTest&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	Vector3 mStartPos;
};
