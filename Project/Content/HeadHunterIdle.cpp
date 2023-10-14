#include "pch.h"
#include "HeadHunterIdle.h"
#include "HeadHunterAI.h"
#include <Engine/EngineMath.h>
HeadHunterIdle::HeadHunterIdle()
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
		//GetMonsterFSM()->ChangeState(HeadHunterAI::Aim);

		int rand = helper::rand::RandInt(0, 100000) % 2;

		for (int i = 0; i < 100; ++i)
		{
			rand = helper::rand::RandInt(0, 100000) % 2;
		}

		if (rand ==  0)
		{
			GetMonsterFSM()->ChangeState(HeadHunterAI::LandDash);
		}
		else if (rand == 1)
		{			
			GetMonsterFSM()->ChangeState(HeadHunterAI::Aim);
		}		
		else if (rand == 2)
		{
			GetMonsterFSM()->ChangeState(HeadHunterAI::TelportShot);
		}

		/*else
		{
			GetMonsterFSM()->ChangeState(HeadHunterAI::BoomShot);
		}*/
	}
}

void HeadHunterIdle::Enter()
{
	mAnimator2D->Play(L"Idle", true);
}

void HeadHunterIdle::Exit()
{
}

