#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(GalssWindow);

class GalssWindow : public ScriptComponent
{
public:
	GalssWindow();
	virtual ~GalssWindow();
	GalssWindow(const GalssWindow&) = delete;
	GalssWindow& operator=(const GalssWindow&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	GameObject* InstantiateGlass();

	virtual void onCollisionEnter(Collider2D* other) override;

};
