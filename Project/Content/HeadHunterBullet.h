#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(HeadHunterBullet);

class HeadHunterBullet : public ScriptComponent
{
public:
	HeadHunterBullet();
	virtual ~HeadHunterBullet();
	HeadHunterBullet(const HeadHunterBullet&) = delete;
	HeadHunterBullet& operator=(const HeadHunterBullet&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
