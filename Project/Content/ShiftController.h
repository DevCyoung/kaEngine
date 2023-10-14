#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

class Light2D;

REGISTER_SCRIPTCOMPONENT_TYPE(ShiftController);

class ShiftController : public ScriptComponent
{
public:
	ShiftController();
	virtual ~ShiftController();
	ShiftController(const ShiftController&) = delete;
	ShiftController& operator=(const ShiftController&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	

	Light2D* mLight;
	GameObject* mPlayer;
	GameObject* mBattery[11];
	Vector4 mPrevBackgorundColor;
	float mTimeScale;
};
