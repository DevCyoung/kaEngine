#include "pch.h"
#include "HeadHunterSweep.h"
#include "GameManager.h"
#include "HeadHunterAI.h"
#include "HeadHunterLazer.h"
HeadHunterSweep::HeadHunterSweep()
	: mSweepState(eSweepState::None)
	, mbLeft(true)
	, mSweepCount(0)
	, mSweepLazer(nullptr)
{
}

HeadHunterSweep::~HeadHunterSweep()
{
}

void HeadHunterSweep::Initialize()
{
	MonsterState::Initialize();
}

void HeadHunterSweep::Update()
{
	switch (mSweepState)
	{
	case eSweepState::None:
		break;
	case eSweepState::Sweep:		
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			mAnimator2D->Play(L"SweepOut", false);
			mSweepState = eSweepState::Out;
			mSweepLazer->GetComponent<HeadHunterLazer>()->TurnOffLazer();
			return;
		}

		{
			GameObject* hand = mGameObject->GetComponent<HeadHunterAI>()->GetHand();
			Transform* handTransform = hand->GetComponent<Transform>();

			Vector3 rotation = handTransform->GetRotation();

			rotation.z -= gDeltaTime * 180.f * 0.95f;
			handTransform->SetRotation(rotation);
		}		
		break;
	case eSweepState::In:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			mAnimator2D->Play(L"Sweep", false);
			mSweepState = eSweepState::Sweep;
			Shot();
			gSoundManager->Play(eResAudioClip::HeadHunter_circle, 1.f);
			--mSweepCount;
			
		}
		break;
	case eSweepState::Out:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{			
			if (mSweepCount <= 0)
			{
				GetMonsterFSM()->ChangeState(HeadHunterAI::TelportShotGround);
			}
			else
			{
				SweepIn();
			}			
		}
		break;
	default:
		break;
	}
}

void HeadHunterSweep::Enter()
{		
	mRigidbody2D->TurnOffGravity();
	mSweepCount = 2;
	SweepIn();


	//gSoundManager->Play(eResAudioClip::HeadHunter_groundLazer, 0.5f);

	//Shoot								
	//GameObject* hand = mGameObject->GetComponent<HeadHunterAI>()->GetHand();
	//GameObject* copyHand = mGameObject->GetComponent<HeadHunterAI>()->CreateHand();

	//Transform* handTransform = hand->GetComponent<Transform>();
	//Transform* copyHandTransform = copyHand->GetComponent<Transform>();

	//copyHandTransform->SetPosition(handTransform->GetPosition());
	//copyHandTransform->SetRotation(handTransform->GetRotation());
	//copyHandTransform->SetScale(handTransform->GetScale());

	////Add copyHand
	//mGameObject->GetGameSystem()->GetScene()->RegisterEventAddGameObject(copyHand, eLayerType::Default);
	//copyHand->SetParent(mGameObject);
	//Shot();
}


void HeadHunterSweep::Exit()
{
	mRigidbody2D->TurnOnGravity();
	mSweepState = eSweepState::None;
}

void HeadHunterSweep::SweepIn()
{
	if (mbLeft)
	{
		mTransform->SetPosition(-440, 120, 0.f);		
	}
	else
	{
		mTransform->SetPosition(440, 120, 0.f);
	}

	mTransform->SetFlipx(mbLeft);
	mAnimator2D->Play(L"SweepIn", false);
	mSweepState = eSweepState::In;

	mbLeft = !mbLeft;


	GameObject* hand = mGameObject->GetComponent<HeadHunterAI>()->GetHand();

	Transform* handTransform = hand->GetComponent<Transform>();
	handTransform->SetRotation(0.f, 0.f, 0.f);
}

void HeadHunterSweep::Shot()
{
	gSoundManager->Play(eResAudioClip::HeadHunter_groundLazer, 0.5f);

	GameObject* hand = mGameObject->GetComponent<HeadHunterAI>()->GetHand();


	//hand->GetComponent<Transform>()->SetRotation(0.f, 0.f, 180.f);

	GameObject* layzer = mGameObject->GetComponent<HeadHunterAI>()->CreateLazer();
	layzer->SetParent(hand);
	layzer->GetComponent<HeadHunterLazer>()->Shot(eLazerState::InAndOutLockOn);
	layzer->GetComponent<HeadHunterLazer>()->TurnOnLazer();

	mGameObject->GetGameSystem()->GetScene()->RegisterEventAddGameObject(layzer, eLayerType::MonsterAttack);

	mSweepLazer = layzer;
}
