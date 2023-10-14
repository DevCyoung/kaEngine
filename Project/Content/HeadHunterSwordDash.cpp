#include "pch.h"
#include "HeadHunterSwordDash.h"
#include "HeadHunterAI.h"
#include "MonsterState.h"
#include "GameManager.h"
#include <Engine/EngineMath.h>
#include <Engine/AfterImage.h>
HeadHunterSwordDash::HeadHunterSwordDash()
	: mSwordDashState(eSwordDashState::None)
	, mDashTime(0.f)
	, mbLeft(true)
{
}

HeadHunterSwordDash::~HeadHunterSwordDash()
{
}

void HeadHunterSwordDash::Initialize()
{
	MonsterState::Initialize();
}

void HeadHunterSwordDash::Update()
{
	switch (mSwordDashState)
	{
	case eSwordDashState::None:
		break;
	case eSwordDashState::PreDash:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			mSwordDashState = eSwordDashState::Dash;

			if (mbLeft)
			{
				mRigidbody2D->SetVelocity(Vector2::Left * 2500.f);
			}
			else
			{
				mRigidbody2D->SetVelocity(Vector2::Right * 2500.f);
			}

			gSoundManager->Play(eResAudioClip::HeadHunter_dash, 0.5f);

			//mRigidbody2D->SetVelocity(Vector2::Left * 100.f);
			mAnimator2D->Play(L"Dash", true);
		}
		break;
	case eSwordDashState::Dash:
	{
		mDashTime += gDeltaTime;

		/*Vector3 position = mTransform->GetPosition();
		if (mbLeft)
		{
			position.x -= 2000.f * gDeltaTime;
		}
		else
		{
			position.x += 2000.f * gDeltaTime;
		}
		
		mTransform->SetPosition(position);*/

		if (mDashTime >= 0.25f)
		{
			Vector2 veolocity = mRigidbody2D->GetVelocity();
			mSwordDashState = eSwordDashState::DashEndGround;
			mAnimator2D->Play(L"DashEndGround", false);
			veolocity.x = 0.f;
			mRigidbody2D->SetVelocity(veolocity);
		}
	}
	break;
	case eSwordDashState::DashEndGround:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			mSwordDashState = eSwordDashState::None;			
			GetMonsterFSM()->ChangeState(HeadHunterAI::Idle);
		}

	break;
	default:
		break;
	}
}

void HeadHunterSwordDash::Enter()
{
	mSwordDashState = eSwordDashState::PreDash;
	mAnimator2D->Play(L"PreDash", false);
	mDashTime = 0.f;

	GameObject* player = GameManager::GetInstance()->GetPlayer();

	Vector2 direction = helper::math::GetDirection2D(mGameObject, player);
	mbLeft = direction.x < 0.f;
	mTransform->SetFlipx(mbLeft);

	mGameObject->GetComponent<AfterImage>()->SetCreateDeltaTime(0.000125f);	
}

void HeadHunterSwordDash::Exit()
{
	mGameObject->GetComponent<AfterImage>()->SetCreateDeltaTime(0.01f);
}


