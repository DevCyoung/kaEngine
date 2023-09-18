#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(SimpleDrawPoint);

class SimpleDrawPoint : public ScriptComponent
{
public:
	SimpleDrawPoint();
	virtual ~SimpleDrawPoint();
	SimpleDrawPoint(const SimpleDrawPoint&) = delete;
	SimpleDrawPoint& operator=(const SimpleDrawPoint&) = delete;

public:
	GameObject* origin;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
