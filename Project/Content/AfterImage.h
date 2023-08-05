#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(AfterImage);

class AfterImage : public ScriptComponent
{
public:
	AfterImage();
	virtual ~AfterImage();
	AfterImage(const AfterImage&) = delete;
	AfterImage& operator=(const AfterImage&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
