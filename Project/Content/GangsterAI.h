#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

#include "PathNode.h"
#include "GameManager.h"
#include "PlayerPath.h"

class Transform;
class Rigidbody2D;
class Animator2D;

REGISTER_SCRIPTCOMPONENT_TYPE(GangsterAI);

enum class eGangsterState
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

class GangsterAI : public ScriptComponent
{
public:
	GangsterAI();
	virtual ~GangsterAI();
	GangsterAI(const GangsterAI&) = delete;
	GangsterAI& operator=(const GangsterAI&) = delete;

	void SetHandObject(GameObject* const handObject) { Assert(handObject, WCHAR_IS_NULLPTR); mHandObject = handObject; }
	void SetGunObject(GameObject* const gunObject) { Assert(gunObject, WCHAR_IS_NULLPTR); mGunObject = gunObject; }

	void trace();

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	bool isAttackable(const float attackDistacne);

	void idle();
	void walk();
	void turn();
	void aim();
	void whip();

	void partrol();
	void search();

	void ChangeState(eGangsterState state);

	


private:
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

	float mShotDelayTime;
	
	std::queue<PathNode*> mPath;
	eGangsterState mState;
};
