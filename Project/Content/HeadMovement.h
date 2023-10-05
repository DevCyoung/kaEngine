#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(HeadMovement);

enum class eHeadState
{
	None,
	Fly,
	FlyLoop,
	Land,
};

class HeadMovement : public ScriptComponent
{
public:
	HeadMovement();
	virtual ~HeadMovement();
	HeadMovement(const HeadMovement&) = delete;
	HeadMovement& operator=(const HeadMovement&) = delete;

	void TurnOnHead(Vector2 direction);


private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	virtual void onCollisionEnter(Collider2D* other) override final;


	bool mbTurnOnHead;
	eHeadState mState;
};
