#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

class B : public ScriptComponent
{
public:
	B();
	virtual ~B();
	B(const B&) = delete;
	B& operator=(const B&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};

REGISTER_SCRIPTCOMPONENT_TYPE(B);
