#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

class Light2D;

REGISTER_SCRIPTCOMPONENT_TYPE(ShiftController);

#define BATTERY_COUNT 11

enum class eSlomoState
{
	None,
	Slomo
};

class ShiftController : public ScriptComponent
{
public:
	ShiftController();
	virtual ~ShiftController();
	ShiftController(const ShiftController&) = delete;
	ShiftController& operator=(const ShiftController&) = delete;

	void AddLight(GameObject* _Light) { mLights.push_back(_Light); }

	void EnterSlomo();
	void ExitSlomo();

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	

	Light2D* mLight;
	GameObject* mPlayer;
	GameObject* mBattery[BATTERY_COUNT];
	std::vector<GameObject*> mLights;
	Vector4 mPrevBackgorundColor;
	float mTimeScale;

	float mSlomoGage;
	eSlomoState mSlomoState;
};
