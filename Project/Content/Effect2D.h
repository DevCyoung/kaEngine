#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(Effect2D);

class Effect2D : public ScriptComponent
{
public:
	Effect2D();
	virtual ~Effect2D();
	Effect2D(const Effect2D&) = delete;
	Effect2D& operator=(const Effect2D&) = delete;

	void SetVelocity(const Vector2& velocity) { mDirection = velocity; }
	void SetSpeed(float speed) { mSpeed = speed; }	

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	

	Vector2 mDirection;
	float mSpeed;
};
