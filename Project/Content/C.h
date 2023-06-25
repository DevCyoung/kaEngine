#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

class C : public ScriptComponent
{
public:
	C();
	virtual ~C();
	C(const C&) = delete;
	C& operator=(const C&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};

REGISTER_SCRIPTCOMPONENT_TYPE(C);
