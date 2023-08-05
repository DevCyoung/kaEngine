#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(FolowPlayer);

class Transform;

class FolowPlayer : public ScriptComponent
{
public:
	FolowPlayer();
	virtual ~FolowPlayer();
	FolowPlayer(const FolowPlayer&) = delete;
	FolowPlayer& operator=(const FolowPlayer&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void fixedUpdate() override final;
	virtual void lateUpdate() override final;
	virtual void lastUpdate() override final;

	Transform* mPlayerTransform;

};
