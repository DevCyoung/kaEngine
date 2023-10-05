#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(MonsterAttack);

class MonsterAttack : public ScriptComponent
{
public:
	MonsterAttack();
	virtual ~MonsterAttack();
	MonsterAttack(const MonsterAttack&) = delete;
	MonsterAttack& operator=(const MonsterAttack&) = delete;

	void SetAttackDirection(const Vector2& attackDirection) { mAttackDirection = attackDirection; }
	Vector2 GetAttackDirection() const { return mAttackDirection; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	Vector2 mAttackDirection;
};
