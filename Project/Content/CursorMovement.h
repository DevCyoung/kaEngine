#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(CursorMovement);

class CursorMovement : public ScriptComponent
{
public:
	CursorMovement();
	virtual ~CursorMovement();
	CursorMovement(const CursorMovement&) = delete;
	CursorMovement& operator=(const CursorMovement&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};
