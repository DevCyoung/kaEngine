#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(BlaBLa);

class BlaBLa : public ScriptComponent
{
public:
	BlaBLa();
	virtual ~BlaBLa();
	BlaBLa(const BlaBLa&) = delete;
	BlaBLa& operator=(const BlaBLa&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};
