#pragma once
#include "FSMState.h"


class GameObject;
class PlayerFSM;

class Rigidbody2D;
class Animator2D;
class Transform;
class Rect2DInterpolation;

class PlayerState : public FSMState
{
public:
	PlayerState(GameObject* const gameObject, PlayerFSM* const owner);

	virtual ~PlayerState() {};
	virtual void Initialize();
	virtual void InputUpdate() = 0;
	virtual void Update() = 0 ;
	virtual void Enter() override {};
	virtual void Exit()  override {};

protected:
	GameObject* mGameObject;
	PlayerFSM* mOwner;

	Transform* mTransform;
	Rigidbody2D* mRigidbody;
	Animator2D* mAnimator;
	Rect2DInterpolation* mInter;
};

