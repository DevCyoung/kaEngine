#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(PickPixelTest);

class PickPixelTest : public ScriptComponent
{
public:
	PickPixelTest();
	virtual ~PickPixelTest();
	PickPixelTest(const PickPixelTest&) = delete;
	PickPixelTest& operator=(const PickPixelTest&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
