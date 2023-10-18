#include "pch.h"
#include "PlayerHurtState.h"
#include "Components.h"
#include "PlayerFSM.h"
#include <Engine/EngineMath.h>
#include "GameManager.h"
PlayerHurtState::PlayerHurtState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
	, mDirection(Vector2::Zero)
	, mEffectTime(0.f)
{
}

PlayerHurtState::~PlayerHurtState()
{
}

void PlayerHurtState::InputUpdate()
{
}

void PlayerHurtState::Update()
{
	Vector3 position = mGameObject->GetComponent<Transform>()->GetPosition();
	Vector2 position2D = Vector2(position.x, position.y);

	Physics2D* const physics = mGameObject->GetGameSystem()->GetPhysics2D();

	RayCast2DHitInfo hitInfo = {};
	if (physics->RayCastHit2D(position2D, Vector2::Down, 40.f, eLayerType::Wall, &hitInfo)       || 
		physics->RayCastHit2D(position2D, Vector2::Down, 70.f, eLayerType::LeftSlope, &hitInfo)  ||
		physics->RayCastHit2D(position2D, Vector2::Down, 70.f, eLayerType::RightSlope, &hitInfo) ||
		physics->RayCastHit2D(position2D, Vector2::Down, 40.f, eLayerType::Platform, &hitInfo))
	{
		(void)position;
		int a = 5;
		(void)a;
		//mAnimator->Play(L"HurtGround", false);

		mOwner->ChangeState(mOwner->mPlayerHurtGroundState);
	}


	mEffectTime += gDeltaTime;

	if (mEffectTime > 0.03f && false == mRigidbody->IsStop())
	{
		mEffectTime = 0.f;

		Vector3 pos = mTransform->GetPosition();
		pos.y -= 25.f;

		for (int i = 0; i < 4; i++)
		{
			int rand = helper::rand::RandInt(0, 10000) % 20;

			pos.x += rand - 10.f;
			pos.y += rand - 10.f;

			if (mTransform->GetFlipX())
			{
				gEffectManager->Shot(L"Blood1", pos, Vector2(0.7f, 0.3f), 350.f);
			}
			else
			{
				gEffectManager->Shot(L"Blood3", pos, Vector2(-0.7f, 0.3f), 350.f);
			}
		}
	}






	DebugRenderer2D* const debugRenderer = mGameObject->GetGameSystem()->GetRenderTargetRenderer()->GetDebugRenderer2D();

	debugRenderer->DrawLine2D2(position, Vector2::Down, 40.f, 0.f, Vector4(1.f, 0.f, 0.f, 1.f));

}

void PlayerHurtState::Enter()
{
	mAnimator->Play(L"HurtFlyLoop", true);

	//Direction setting
	Vector3 position = mTransform->GetComponent<Transform>()->GetPosition();
	position.y += 15.f;
	mTransform->SetPosition(position);

	//MonsterAttack

	Vector2 velocity = Vector2(mDirection.x * 500.f, 300.f);	
	mTransform->SetFlipx(mDirection.x > 0.f);	

	mRigidbody->SetVelocity(velocity);
}

void PlayerHurtState::Exit()
{
}
