#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(Bugiman);

class Bugiman : public ScriptComponent
{
public:
	Bugiman();
	virtual ~Bugiman();
	Bugiman(const Bugiman&) = delete;
	Bugiman& operator=(const Bugiman&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	
};
