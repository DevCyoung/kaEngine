#include "pch.h"
#include "PlayerState.h"
#include "PlayerFSM.h"
#include "Components.h"
#include "Rect2DInterpolation.h"

PlayerState::PlayerState(GameObject* const gameObject, PlayerFSM* const owner)
	: mGameObject(gameObject)
	, mOwner(owner)
	, mTransform(nullptr)
	, mAnimator(nullptr)
	, mRigidbody(nullptr)
	, mInter(nullptr)
{
}

void PlayerState::Initialize()
{
	mTransform	= mGameObject->GetComponent<Transform>();
	mRigidbody	= mGameObject->GetComponent<Rigidbody2D>();
	mAnimator	= mGameObject->GetComponent<Animator2D>();
	mInter		= mGameObject->GetComponent<Rect2DInterpolation>();
}

void PlayerState::InputUpdate()
{
}

void PlayerState::Update()
{
}
