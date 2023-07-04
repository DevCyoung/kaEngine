#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(ShiftController);

class ShiftController : public ScriptComponent
{
public:
	ShiftController();
	virtual ~ShiftController();
	ShiftController(const ShiftController&) = delete;
	ShiftController& operator=(const ShiftController&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	
};
