#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(ParentTest);

class ParentTest : public ScriptComponent
{
public:
	ParentTest();
	virtual ~ParentTest();
	ParentTest(const ParentTest&) = delete;
	ParentTest& operator=(const ParentTest&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;


	float mSclae;
};
