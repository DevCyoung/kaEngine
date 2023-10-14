#include "pch.h"
#include "HeadHunterHurt.h"
#include <Engine/EngineMath.h>
#include "GameManager.h"
#include <Engine/EngineMath.h>
#include "HeadHunterAI.h"
#include "MonsterFSM.h"
HeadHunterHurt::HeadHunterHurt()
	: mHurtState(eHurtState::None)
	, mHurtTime(0.f)
{
}

HeadHunterHurt::~HeadHunterHurt()
{
}

void HeadHunterHurt::Initialize()
{
	MonsterState::Initialize();
}

void HeadHunterHurt::Update()
{
	Physics2D* physics2D = mGameObject->GetGameSystem()->GetPhysics2D();
	Vector3 position = mTransform->GetPosition();
	Vector2 velocity = mRigidbody2D->GetVelocity();
	RayCast2DHitInfo hitInfo = {};	

	if (mHurtState  == eHurtState::HurtFly && physics2D->RayCastHit2D(Vector2(position.x, position.y), Vector2::Down, 50.f, eLayerType::Wall, &hitInfo))
	{		
		mAnimator2D->Play(L"Hurt", false);
		velocity.x = 0.f;
		mRigidbody2D->SetVelocity(velocity);
		mHurtState = eHurtState::HurtGround;
		//GetMonsterFSM()->ChangeState(HeadHunterAI::Idle);		
	}
	else if (mHurtState == eHurtState::HurtGround)
	{
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			Vector3 pos = mTransform->GetPosition();
			
			gSoundManager->Play(eResAudioClip::HeadHunter_vanish, 0.5f);			

			for (int i = 0; i < 25; ++i)
			{
				float xOffset = static_cast<float>(helper::rand::RandInt(-100, 100));
				float yOffset = static_cast<float>(helper::rand::RandInt(-100, 100));

				

				pos = mTransform->GetPosition();				
				pos.x += xOffset;
				pos.y += yOffset;
				Vector2 direction = helper::math::GetDirection2D(mTransform->GetPosition(), pos);
				float deg = Rad2Deg(atan2(direction.y, direction.x));
				//rotation.z = 10.f;				

				Vector3 rotation = Vector3::Zero;
				rotation.z = deg;				
				gEffectManager->Shot(L"GunSpark2", pos, rotation, false);
				gEffectManager->Shot(L"GunSmoke3", pos, rotation, false);
			}
	
			mAnimator2D->Play(L"Invisible", false);			
			mHurtState = eHurtState::TelportShotReady;
		}
	}
	else if (mHurtState == eHurtState::TelportShotReady)
	{
		mHurtTime += gDeltaTime;

		if (mHurtTime >= 1.6f)
		{
			GetMonsterFSM()->ChangeState(HeadHunterAI::TelportShot);
		}

	}
}

void HeadHunterHurt::Enter()
{
	mAnimator2D->Play(L"HurtFly", true);
	mHurtState = eHurtState::HurtFly;

	mHurtTime = 0.f;
}

void HeadHunterHurt::Exit()
{
}
