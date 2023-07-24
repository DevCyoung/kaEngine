#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(Rect2DInterpolation);

class Rect2DInterpolation : public ScriptComponent
{
public:
	Rect2DInterpolation();
	virtual ~Rect2DInterpolation();
	Rect2DInterpolation(const Rect2DInterpolation&) = delete;
	Rect2DInterpolation& operator=(const Rect2DInterpolation&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	virtual void onCollisionEnter(Collider2D* other) override;
	virtual void onCollisionStay(Collider2D* other) override;
	virtual void onCollisionExit(Collider2D* other) override;
};
