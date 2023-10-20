#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(DoorController);

class DoorController : public ScriptComponent
{
public:
	DoorController();
	virtual ~DoorController();
	DoorController(const DoorController&) = delete;
	DoorController& operator=(const DoorController&) = delete;

	bool IsOpen() const { return mbOpen; }

	void Open(GameObject* const opener);

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	virtual void onCollisionEnter(Collider2D* other) override;


	bool mbOpen;
};
