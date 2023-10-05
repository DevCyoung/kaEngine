#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(SlashComponent);

class SlashComponent : public ScriptComponent
{
public:
	SlashComponent();
	virtual ~SlashComponent();
	SlashComponent(const SlashComponent&) = delete;
	SlashComponent& operator=(const SlashComponent&) = delete;

	void slashSouind();

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
