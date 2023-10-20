#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(ClearController);

class ClearController : public ScriptComponent
{
public:
	ClearController();
	virtual ~ClearController();
	ClearController(const ClearController&) = delete;
	ClearController& operator=(const ClearController&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void onCollisionEnter(Collider2D* other) override final;
};
