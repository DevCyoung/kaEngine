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
	Block,
	Hurt,

	Slash, // 1

	Jump, // 2
	JumpSwing,

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

	void slash();
	void Idle();

	void preLunge();
	void lunge();
	void lungeAttack();

	void _throw();
	void tug();
	void returnAxe();

	void throwAxe();

	


	Animator2D* mAnimator2D;
	Rigidbody2D* mRigidbody2D;
	Vector2 mDirection;
	eKissyfaceAIState mState;

	GameObject* mAxe;
};
