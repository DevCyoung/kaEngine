#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include "Components.h"
#include "PathNode.h"
#include "GameManager.h"
#include "PlayerPath.h"
#include "RewindComponent.h"

enum class eMonsterState
{
	Idle,
	Partrol,
	Turn,
	Walk,
	Trace,
	Attack,
	Aim,
	Whip,
	Fall,
	HurtFly,
	HurtGround,
	Dead,
};

class BasicMonsterAI : public ScriptComponent
{
public:
	BasicMonsterAI(const eScriptComponentType scriptComponentType);
	virtual ~BasicMonsterAI();
	BasicMonsterAI(const BasicMonsterAI&) = delete;
	BasicMonsterAI& operator=(const BasicMonsterAI&) = delete;

	void SetHandObject(GameObject* const handObject) { Assert(handObject, WCHAR_IS_NULLPTR); mHandObject = handObject; }
	void SetGunObject(GameObject* const gunObject) { Assert(gunObject, WCHAR_IS_NULLPTR); mGunObject = gunObject; }
	void ChangeState(eMonsterState state);


	virtual void CreateAnimation(Scene* scene) = 0;
	virtual void CreateGun(Scene* scene) = 0;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;			

	virtual void onCollisionEnter(Collider2D* other) override;

	

protected:
	bool isAttackable(const float attackDistacne);
	virtual void trace();
	virtual void idle();
	virtual void walk();
	virtual void turn();
	virtual void aim();
	virtual void whip();
	virtual void partrol();
	virtual void search();


protected:
	PathNode* mPrePlayerPathNode;
	GameObject* mHandObject;
	GameObject* mGunObject;
	Transform* mTransform;
	Animator2D* mAnimator2D;
	Rigidbody2D* mRigidbody2D;

	float mRunSpeed;
	float mPatrolDitance;

	float mCurIdleTime;
	float mCurWalkTime;

	float mElevatorTime;

	float mShotDelayTime;

	float mEffectTime;

	std::queue<PathNode*> mPath;
	eMonsterState mState;

	bool mbDead;
};
