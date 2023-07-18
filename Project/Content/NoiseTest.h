#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
class Material;

REGISTER_SCRIPTCOMPONENT_TYPE(NoiseTest);

class NoiseTest : public ScriptComponent
{
public:
	NoiseTest();
	virtual ~NoiseTest();
	NoiseTest(const NoiseTest&) = delete;
	NoiseTest& operator=(const NoiseTest&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	Material* matArray[4];
};
