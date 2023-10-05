#include "pch.h"
#include "PlayerRollState.h"
#include "PlayerFSM.h"
#include "Components.h"
#include "GameManager.h"
#include <Engine/EngineMath.h>

PlayerRollState::PlayerRollState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
	, time(0.f)
	, effectTime(0.f)
	, prevDirX(0.f)	
{
}

PlayerRollState::~PlayerRollState()
{
}

void PlayerRollState::InputUpdate()
{
}

void PlayerRollState::Update()
{		
	time += gDeltaTime;

	mOwner->mPlayerGlobalState->InputFlip();
	Vector2 right = Vector2::Right * prevDirX;
	//
	//if (abs(mRigidbody->GetVelocity().x) > 650.f)
	//{
	//	mRigidbody->SetVelocity(right * 650.f);
	//}
	//else
	//{
	//	mRigidbody->AddForce(right * 8000.f);
	//}

	effectTime += gDeltaTime;

	

	
	if (effectTime > 0.04f)
	{
		effectTime = 0.f;

		Vector3 position = mTransform->GetPosition();

		position.y -= 25.f;

		for (int i = 0; i < 3; i++)
		{
			int rand = helper::rand::RandInt(0, 10000) % 20;

			position.x += rand - 10.f;
			position.y += rand - 10.f;

			//position.y

			if (mTransform->GetFlipX())
			{
				gEffectManager->Shot(L"DustCloud", position, Vector2(0.7f, 0.3f), 350.f);
			}
			else
			{
				gEffectManager->Shot(L"DustCloud", position, Vector2(-0.7f, 0.3f), 350.f);
			}
		}		
	}
	

	if (time > 0.3f)
	{
		mAnimator->Play(L"RunToIdle", false);
		mOwner->ChangeState(mOwner->mPlayerIdleState);
		mRigidbody->SetVelocity(right * 10.f);		
		return;
	}
}

void PlayerRollState::Enter()
{
	mAnimator->Play(L"Roll", false);
	time = 0.f;

	Vector2 dir = mOwner->mPlayerGlobalState->GetInputDirectionX();
	prevDirX = dir.x;

	mOwner->mPlayerGlobalState->InputFlip();
	Vector2 right = Vector2::Right * prevDirX;
	mRigidbody->SetVelocity(right * 700);
}

void PlayerRollState::Exit()
{
}
