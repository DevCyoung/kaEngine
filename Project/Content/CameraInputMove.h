#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(CameraInputMove);

class CameraInputMove : public ScriptComponent
{
public:
	CameraInputMove();
	virtual ~CameraInputMove();
	CameraInputMove(const CameraInputMove&) = delete;
	CameraInputMove& operator=(const CameraInputMove&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};
