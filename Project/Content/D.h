#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

class D : public ScriptComponent
{
public:
	D();
	virtual ~D();
	D(const D&) = delete;
	D& operator=(const D&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};

REGISTER_SCRIPTCOMPONENT_TYPE(D);
