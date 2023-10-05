#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(PlayerController);

class PlayerFSM;
class GameObject;

class PlayerController : public ScriptComponent
{
public:
	PlayerController();
	virtual ~PlayerController();
	PlayerController(const PlayerController&) = delete;
	PlayerController& operator=(const PlayerController&) = delete;

	void SetFSM(PlayerFSM* const playerFSM) { mPlayerFSM = playerFSM; }
	void ChangeHurtState();
	void SetSlash(GameObject* const slash) { mSlash = slash; }

	GameObject* GetSlash() const { return mSlash; }

	bool IsControl() const { return mbControl; }
	bool IsInvincibility() const { return mbinvincibility; }

	void SetControl(bool bControl) { mbControl = bControl; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	virtual void onCollisionEnter(Collider2D* other) override final;

	void idleToRun();
	void runToIdle();
	void runToIdleVeloZero();
	void toFall();

	bool mbControl;
	bool mbinvincibility;

	PlayerFSM* mPlayerFSM;
	GameObject* mSlash;
};
