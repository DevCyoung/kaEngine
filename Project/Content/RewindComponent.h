#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(RewindComponent);

class RewindComponent : public ScriptComponent
{
public:
	RewindComponent();
	virtual ~RewindComponent();
	RewindComponent(const RewindComponent&) = delete;
	RewindComponent& operator=(const RewindComponent&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
