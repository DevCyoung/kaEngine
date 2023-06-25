#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

class E : public ScriptComponent
{
public:
	E();
	virtual ~E();
	E(const E&) = delete;
	E& operator=(const E&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};

REGISTER_SCRIPTCOMPONENT_TYPE(E);
