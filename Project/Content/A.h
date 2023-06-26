#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

class A : public ScriptComponent
{
public:
	A();
	virtual ~A();
	A(const A&) = delete;
	A& operator=(const A&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};

REGISTER_SCRIPTCOMPONENT_TYPE(A);
