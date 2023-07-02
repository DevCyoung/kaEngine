#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(UIEffect);

class UIEffect : public ScriptComponent
{
public:
	UIEffect();
	virtual ~UIEffect();
	UIEffect(const UIEffect&) = delete;
	UIEffect& operator=(const UIEffect&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;

private:
	float x;
};
