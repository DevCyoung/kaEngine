#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(SlashEffectMovement);

class SlashEffectMovement : public ScriptComponent
{
public:
	SlashEffectMovement();
	virtual ~SlashEffectMovement();
	SlashEffectMovement(const SlashEffectMovement&) = delete;
	SlashEffectMovement& operator=(const SlashEffectMovement&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
