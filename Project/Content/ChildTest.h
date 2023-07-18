#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(ChildTest);

class ChildTest : public ScriptComponent
{
public:
	ChildTest();
	virtual ~ChildTest();
	ChildTest(const ChildTest&) = delete;
	ChildTest& operator=(const ChildTest&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
