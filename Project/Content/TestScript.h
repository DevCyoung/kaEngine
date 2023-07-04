#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(TestScript);

class TestScript : public ScriptComponent
{
public:
	TestScript();
	virtual ~TestScript();
	TestScript(const TestScript&) = delete;
	TestScript& operator=(const TestScript&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
