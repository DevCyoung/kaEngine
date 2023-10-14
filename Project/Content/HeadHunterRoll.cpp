#include "pch.h"
#include "HeadHunterRoll.h"
#include "MonsterFSM.h"
#include "HeadHunterAI.h"

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
	Vector2 left = Vector2(-1.f, 0.3f);
	mRigidbody2D->SetVelocity(left * 600.f);
}

void HeadHunterRoll::Exit()
{
}
