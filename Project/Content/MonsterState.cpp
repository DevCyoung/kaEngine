#include "pch.h"
#include "MonsterState.h"
#include "MonsterFSM.h"

MonsterState::MonsterState()
	: mTransform(nullptr)
	, mAnimator2D(nullptr)
	, mRigidbody2D(nullptr)
	, mMonsterFSM(nullptr)
	, mGameObject(nullptr)
	, mType(0)
{
}

MonsterState::~MonsterState()
{
}

void MonsterState::Initialize()
{
	mTransform = mGameObject->GetComponent<Transform>();
	mAnimator2D = mGameObject->GetComponent<Animator2D>();
	mRigidbody2D = mGameObject->GetComponent<Rigidbody2D>();
}
