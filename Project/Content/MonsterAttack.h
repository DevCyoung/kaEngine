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

	void SetAttackAble(bool bAttackAble) { mbAttackAble = bAttackAble; }
	bool GetAttackAble() const { return mbAttackAble; }
	void Shot(float time, Vector3 position, Vector2 scale);

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	

	Vector2 mAttackDirection;
	float mShotTime;
	bool mbShot;
	bool mbBack;
	bool mbAttackAble;
};
