#include "pch.h"
#include "HeadHunterPreJump.h"
#include "MonsterFSM.h"
#include "HeadHunterAI.h"
#include <Engine/EngineMath.h>
#include "GameManager.h"

HeadHunterPreJump::HeadHunterPreJump()
	: mState(ePreJumpState::None)
{
}

HeadHunterPreJump::~HeadHunterPreJump()
{
}

void HeadHunterPreJump::Initialize()
{
	MonsterState::Initialize();
}

void HeadHunterPreJump::Update()
{
	Physics2D* physics2D = mGameObject->GetGameSystem()->GetPhysics2D();
	Vector2 direction = mRigidbody2D->GetDirection();
	Vector3 position3D = mTransform->GetPosition();
	Vector2 pos = Vector2(position3D.x, position3D.y);
	RayCast2DHitInfo hitInfo = {};

	if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
	{
		switch (mState)
		{
		case ePreJumpState::None:
			break;
		case ePreJumpState::PreJump:

			if (helper::rand::RandInt(0, 100000) % 2)
			{
				mRigidbody2D->SetVelocity(Vector2(1.f, 1.f) * 900.f);
				mTransform->SetFlipx(true);
			}
			else
			{
				mRigidbody2D->SetVelocity(Vector2(-1.f, 1.f) * 900.f);
				mTransform->SetFlipx(false);
			}


			if (physics2D->RayCastHit2D(pos, Vector2::Left, 40.f, eLayerType::Wall, &hitInfo))
			{
				mRigidbody2D->SetVelocity(Vector2(1.f, 1.f) * 900.f);
				mTransform->SetFlipx(true);
			}
			else if (physics2D->RayCastHit2D(pos, Vector2::Right, 0.f, eLayerType::Wall, &hitInfo))
			{
				mRigidbody2D->SetVelocity(Vector2(-1.f, 1.f) * 900.f);
				mTransform->SetFlipx(false);
			}

			
			mState = ePreJumpState::Jump;
			mAnimator2D->Play(L"Jump", false);
			gSoundManager->Play(eResAudioClip::playerJump, 0.3f);
			break;
		case ePreJumpState::Jump:
		{



			if (direction.x < 0.f)
			{
				direction = Vector2::Left;
			}
			else
			{
				direction = Vector2::Right;
			}

	

			if (physics2D->RayCastHit2D(pos, direction, 30.f, eLayerType::Wall, &hitInfo))
			{
				GetMonsterFSM()->ChangeState(HeadHunterAI::WallJump);
				gSoundManager->Play(eResAudioClip::playerWallKick1, 0.3f);
			}
			else if (physics2D->RayCastHit2D(pos, Vector2::Down, 50.f, eLayerType::Wall, &hitInfo))
			{
				GetMonsterFSM()->ChangeState(HeadHunterAI::Idle);
				gSoundManager->PlayInForce(eResAudioClip::playerLand, 0.3f);
			}
		}
			break;
		default:
			break;
		}
	}
}

void HeadHunterPreJump::Enter()
{
	mAnimator2D->Play(L"PreJump", false);
	mState = ePreJumpState::PreJump;
}

void HeadHunterPreJump::Exit()
{	
}
