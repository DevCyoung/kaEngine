#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(Emotion);

class Emotion : public ScriptComponent
{
public:
	Emotion();
	virtual ~Emotion();
	Emotion(const Emotion&) = delete;
	Emotion& operator=(const Emotion&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
