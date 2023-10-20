#include "pch.h"
#include "HeadHunterTeleport.h"
#include <Engine/EngineMath.h>
#include "MonsterFSM.h"
#include "HeadHunterAI.h"
#include "GameManager.h"
#include "HeadHunterLazer.h"
HeadHunterTeleport::HeadHunterTeleport()
	:mTeleportState(eTeleportState::None)
	,mAttackCount(0)
{
}

HeadHunterTeleport::~HeadHunterTeleport()
{
}

void HeadHunterTeleport::Initialize()
{
	MonsterState::Initialize();
}

void HeadHunterTeleport::Update()
{
	switch (mTeleportState)
	{
	case eTeleportState::None:
		break;
	case eTeleportState::In:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{			
			mTeleportState = eTeleportState::Out;
			mAnimator2D->Play(L"TeleportOut", false);
		}
		break;
	case eTeleportState::Out:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			mAttackCount--;
			if (mAttackCount <= 0)
			{
				GetMonsterFSM()->ChangeState(HeadHunterAI::Sweep);
				return;
			}

			float xPos = static_cast<float>(helper::rand::RandInt(-100000, 100000) % 400);
			mTransform->SetPosition(xPos, 120, 0.f);

			mTeleportState = eTeleportState::In;
			mAnimator2D->Play(L"TeleportIn", false);
			Shot();
		}
		break;	
	default:
		break;
	}
}

void HeadHunterTeleport::Enter()
{
	mRigidbody2D->TurnOffGravity();	
	mTeleportState = eTeleportState::In;
	mAnimator2D->Play(L"TeleportIn", false);	
	mAttackCount = 6;

	float xPos = static_cast<float>(helper::rand::RandInt(-100000, 100000) % 400);
	mTransform->SetPosition(xPos, 120, 0.f);

	Shot();
}

void HeadHunterTeleport::Exit()
{
	mRigidbody2D->TurnOnGravity();
	mTeleportState = eTeleportState::None;
}

void HeadHunterTeleport::Shot()
{
	gSoundManager->Play(eResAudioClip::HeadHunter_lockon, 0.5f);

	//Shoot								
	//GameObject* hand = mGameObject->GetComponent<HeadHunterAI>()->GetHand();
	GameObject* copyHand = mGameObject->GetComponent<HeadHunterAI>()->CreateHand();
	copyHand->SetParent(nullptr);

	//Transform* handTransform = hand->GetComponent<Transform>();
	Transform* copyHandTransform = copyHand->GetComponent<Transform>();

	Vector3 position = mTransform->GetPosition();
	Vector3 copyHandPosition = position;

	position.x += 2.f;

	copyHandTransform->SetPosition(position);
	copyHandTransform->SetRotation(0.f, 0.f, -90.f);
	copyHandTransform->SetScale(2.f, 2.f, 1.f);

	//Add copyHand

	mGameObject->GetGameSystem()->GetScene()->RegisterEventAddGameObject(copyHand, eLayerType::Default);
	//copyHand->SetParent(mGameObject);

	GameObject* layzer = mGameObject->GetComponent<HeadHunterAI>()->CreateLazer();
	mGameObject->GetGameSystem()->GetScene()->RegisterEventAddGameObject(layzer, eLayerType::MonsterAttack);
	layzer->GetComponent<HeadHunterLazer>()->Shot(eLazerState::InAndOutLockOn);
	layzer->SetParent(copyHand);
}
