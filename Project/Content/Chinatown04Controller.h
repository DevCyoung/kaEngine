#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(Chinatown04Controller);

class Chinatown04Controller : public ScriptComponent
{
public:
	Chinatown04Controller();
	virtual ~Chinatown04Controller();
	Chinatown04Controller(const Chinatown04Controller&) = delete;
	Chinatown04Controller& operator=(const Chinatown04Controller&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
