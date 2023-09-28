#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(KissyfaceAI);

class Animator2D;
class Rigidbody2D;

enum class eKissyfaceAIState
{
	None,
	Ready,
	ToBattle,
	

	Idle,
	
	Hurt,	

	Block,

	Slash, // 1

	PreJump, //2
	Jump, 
	JumpSwing,
	LandAttack,

	PreLunge, // 3
	Lunge,
	LungeAttack,

	Throw,
	Tug,
	ReturnAxe,

	Recover,
	Dead,
};

class KissyfaceAI : public ScriptComponent
{
public:
	KissyfaceAI();
	virtual ~KissyfaceAI();
	KissyfaceAI(const KissyfaceAI&) = delete;
	KissyfaceAI& operator=(const KissyfaceAI&) = delete;


	void SetAxe(GameObject* const axe) { Assert(axe, WCHAR_IS_NULLPTR); mAxe = axe; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	void hurt();
	void recover();

	void block();

	void preJump();
	void jump();
	void jumpSwing();
	void landAttack();

	void slash();
	void Idle();

	void preLunge();
	void lunge();
	void lungeAttack();

	void _throw();
	void tug();
	void returnAxe();

	void throwAxe();

	void turnOnVisibleAxe();
	void turnOffVisibleAxe();	

	virtual void onCollisionEnter(Collider2D* other) override;

	bool isAxeInHand();
	bool isAttackable();


	Animator2D* mAnimator2D;
	Rigidbody2D* mRigidbody2D;
	Vector2 mDirection;
	eKissyfaceAIState mState;
	GameObject* mAxe;

	int mLife;

	float mHurtTime;
};
