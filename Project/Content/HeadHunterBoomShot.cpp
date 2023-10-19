#include "pch.h"
#include "HeadHunterBoomShot.h"
#include "HeadHunterAI.h"
#include "GameManager.h"
#include <Engine/EngineMath.h>

HeadHunterBoomShot::HeadHunterBoomShot()
	:mShootCount(0)
	, mBoomShotState(eBoomShotState::None)
{
}

HeadHunterBoomShot::~HeadHunterBoomShot()
{
}

void HeadHunterBoomShot::Initialize()
{
	MonsterState::Initialize();
}


void HeadHunterBoomShot::Update()
{
	GameObject* player = GameManager::GetInstance()->GetPlayer();
	GameObject* handObject = mGameObject;

	Vector2 direction = helper::math::GetDirection2D(handObject, player);
	Vector3 playerPosition = player->GetComponent<Transform>()->GetPosition();

	float distance = helper::math::GetDistance2D(handObject, player);

	if (distance <= 100.f)
	{
		GetMonsterFSM()->ChangeState(HeadHunterAI::Roll);
		return;
	}

	switch (mBoomShotState)
	{
	case eBoomShotState::None:
		break;
	case eBoomShotState::TakeOut:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			mAnimator2D->Play(L"Shoot", false);
			mBoomShotState = eBoomShotState::Shoot;			
		}
		break;
	case eBoomShotState::Shoot:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			mShootCount++;
			mAnimator2D->Play(L"Shoot", false);

			if (mShootCount >= 3)
			{
				mShootCount = 0;
				mBoomShotState = eBoomShotState::PutBack;
				mAnimator2D->Play(L"PutBackGun", false);
			}
		}
		break;
	case eBoomShotState::PutBack:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			GetMonsterFSM()->ChangeState(HeadHunterAI::Idle);
		}		
		break;
	default:
		break;
	}	
}

void HeadHunterBoomShot::Enter()
{
	mShootCount = 0;

	mAnimator2D->Play(L"TakeOutGun", false);
	mBoomShotState = eBoomShotState::TakeOut;

	GameObject* player = GameManager::GetInstance()->GetPlayer();
	Vector2 direction = helper::math::GetDirection2D(mGameObject, player);
	mTransform->SetFlipx(direction.x < 0.f);
}

void HeadHunterBoomShot::Exit()
{
}

