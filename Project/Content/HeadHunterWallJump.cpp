#include "pch.h"
#include "HeadHunterWallJump.h"
#include "MonsterFSM.h"
#include "HeadHunterAI.h"
#include "GameManager.h"
#include "GameObjectBuilder.h"
#include <Engine/EngineMath.h>
#include <Engine/AfterImage.h>

HeadHunterWallJump::HeadHunterWallJump()
	: mWallJumpState(eWallJumpState::None)
	, mJumpTime(45.f)
	, mShotTime(0.f)
	, mBulletCount(0)
{
}

HeadHunterWallJump::~HeadHunterWallJump()
{
}

void HeadHunterWallJump::Initialize()
{
	MonsterState::Initialize();
}

void HeadHunterWallJump::Update()
{
	switch (mWallJumpState)
	{
	case eWallJumpState::None:
		break;
	case eWallJumpState::Idle:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			mWallJumpState = eWallJumpState::Jump;
			mAnimator2D->Play(L"WallJump", false);
			mRigidbody2D->TurnOnGravity();
			Vector3 position = mTransform->GetPosition();

			if (position.x < 0.f)
			{
				mRigidbody2D->SetVelocity(Vector2(1000.f, 1000.f));
				gSoundManager->Play(eResAudioClip::HeadHunter_wallShot, 1.f);
			}
			else
			{
				mRigidbody2D->SetVelocity(Vector2(-1000.f, 1000.f));
				gSoundManager->Play(eResAudioClip::HeadHunter_wallShot, 1.f);
			}
			
			gSoundManager->Play(eResAudioClip::playerRoll, 0.3f);
			//GameObjectBuilder::CreateBullet()

			
		}
		break;
	case eWallJumpState::Jump:
	{
		Physics2D* physics2D = mGameObject->GetGameSystem()->GetPhysics2D();
		Vector3 position = mTransform->GetPosition();
		Vector2 velocity = mRigidbody2D->GetVelocity();
		RayCast2DHitInfo hitInfo = {};

		mJumpTime -= gDeltaTime;
		mShotTime += gDeltaTime;

		Vector3 direction = Vector3( cosf(Deg2Rad(mJumpTime * 360.f)) , sinf(Deg2Rad(mJumpTime * 360.f)), 0.f);


		if (physics2D->RayCastHit2D(Vector2(position.x, position.y), Vector2::Down, 50.f, eLayerType::Wall, &hitInfo))
		{
			mWallJumpState = eWallJumpState::Land;
			mAnimator2D->Play(L"WallJumpLand", false);
			velocity.x = 0.f;
			mRigidbody2D->SetVelocity(velocity);
			//GetMonsterFSM()->ChangeState(HeadHunterAI::Idle);
			gSoundManager->PlayInForce(eResAudioClip::playerLand, 0.3f);
		}
		else if (mShotTime >= 0.018f && mBulletCount < 24)
		{
			GameObject* bullet = GameObjectBuilder::CreateBullet(direction, position, eBulletType::MonsterBullet);
			++mBulletCount;
			mGameObject->GetGameSystem()->GetScene()->RegisterEventAddGameObject(bullet, eLayerType::Bullet);
			mShotTime = 0.f;			
		}
		
	}
	break;

	case eWallJumpState::Land:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			GetMonsterFSM()->ChangeState(HeadHunterAI::Idle);
		}
		break;
	default:
		break;
	}
}

void HeadHunterWallJump::Enter()
{
	mRigidbody2D->TurnOffGravity();	
	mRigidbody2D->SetVelocity(Vector2::Zero);

	mWallJumpState = eWallJumpState::Idle;
	mAnimator2D->Play(L"WallIdle", true);	

	mJumpTime = 0.f;
	mShotTime = 0.f;
	mBulletCount = 0;
}

void HeadHunterWallJump::Exit()
{
	mRigidbody2D->TurnOnGravity();
}
