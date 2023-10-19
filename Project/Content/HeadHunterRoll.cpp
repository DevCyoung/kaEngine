#include "pch.h"
#include "HeadHunterRoll.h"
#include "MonsterFSM.h"
#include "HeadHunterAI.h"
#include <Engine/EngineMath.h>
HeadHunterRoll::HeadHunterRoll()
{
}

HeadHunterRoll::~HeadHunterRoll()
{
}

void HeadHunterRoll::Initialize()
{
	MonsterState::Initialize();
}

void HeadHunterRoll::Update()
{
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		GetMonsterFSM()->ChangeState(HeadHunterAI::Idle);
		mRigidbody2D->SetVelocity(Vector2::Zero);
	}
}

void HeadHunterRoll::Enter()
{
	mAnimator2D->Play(L"Roll", false);
	//int rand = helper::rand::RandInt(0, 100000) % 2;

	Vector3 position = mTransform->GetPosition();

	Vector2 left = Vector2::Left;

	if (position.x < 0.f)
	{
		left = Vector2::Right;
	}	

	mTransform->SetFlipx(left.x < 0.f);
	
	mRigidbody2D->SetVelocity(left * 700.f);
}

void HeadHunterRoll::Exit()
{
}
