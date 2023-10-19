#include "pch.h"
#include "HeadHunterIdle.h"
#include "HeadHunterAI.h"
#include <Engine/EngineMath.h>
HeadHunterIdle::HeadHunterIdle()
	: prevRand(0)
{
}

HeadHunterIdle::~HeadHunterIdle()
{
}

void HeadHunterIdle::Initialize()
{
	MonsterState::Initialize();
}


void HeadHunterIdle::Update()
{	
	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{		
		//GetMonsterFSM()->ChangeState(HeadHunterAI::PreJump);
	}

	////GetMonsterFSM()->ChangeState(HeadHunterAI::Aim);

	int rand = helper::rand::RandInt(0, 100000) % 4;

	//for (int i = 0; i < 100; ++i)
	//{
	//	//rand = helper::rand::RandInt(0, 100000) % 2;
	//}

	if (rand == prevRand)
	{
		rand++;

		if (rand >= 4)
		{
			rand = 0;
		}
	}

	//rand = 3;

	if (rand == 0)
	{
		GetMonsterFSM()->ChangeState(HeadHunterAI::LandDash);
	}
	else if (rand == 1)
	{
		GetMonsterFSM()->ChangeState(HeadHunterAI::Aim);
	}
	else if (rand == 2)
	{
		GetMonsterFSM()->ChangeState(HeadHunterAI::PreJump);
	}
	else if (rand == 3)
	{
		GetMonsterFSM()->ChangeState(HeadHunterAI::BoomShot);
	}

	prevRand = rand;

}

void HeadHunterIdle::Enter()
{
	mAnimator2D->Play(L"Idle", true);
	Vector2 velocity = mRigidbody2D->GetVelocity();
	velocity.x = 0.f;
	mRigidbody2D->SetVelocity(velocity);
}

void HeadHunterIdle::Exit()
{
}

