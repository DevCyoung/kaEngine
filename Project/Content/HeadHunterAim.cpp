#include "pch.h"
#include "HeadHunterAim.h"
#include "GameManager.h"
#include <Engine/EngineMath.h>
#include "GameManager.h"
#include "MonsterFSM.h"
#include "HeadHunterAI.h"
#include "HeadHunterLazer.h"

HeadHunterAim::HeadHunterAim()
	: mShootCount(0)
	, mFrameIdx(0)
	, mAimState(eAimState::None)
	, mShootDelay(0.f)
{
}

HeadHunterAim::~HeadHunterAim()
{
}

void HeadHunterAim::Initialize()
{
	MonsterState::Initialize();
}

void HeadHunterAim::Update()
{
	switch (mAimState)
	{
	case eAimState::None:
		break;

	case eAimState::TakeOut:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			EnterAim();
		}
		break;

	case eAimState::PutBack:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			GetMonsterFSM()->ChangeState(HeadHunterAI::Idle);
		}
		break;

	case eAimState::Aim:
		aim();		
		break;
	case eAimState::LockOn:
		mShootDelay += gDeltaTime;
		if (mShootDelay >= 0.4f)
		{
			++mShootCount;
			rifleShoot();
			EnterAim();
		}
		break;
	case eAimState::Shoot:
		mShootDelay += gDeltaTime;
		if (mShootDelay >= 0.3f)
		{	
			mShootDelay = 0.f;
			EnterAim();
		}		
		break;

	default:
		break;
	}	

	if (eAimState::Aim == mAimState || 
		eAimState::Shoot == mAimState || 
		eAimState::LockOn == mAimState)
	{
		mAnimator2D->PlayFrame(L"Aim", mFrameIdx, false);
	}
}

void HeadHunterAim::Enter()
{
	mShootDelay = 0.f;
	mShootCount = 0;
	mAimState = eAimState::TakeOut;	
	mAnimator2D->Play(L"TakeOutRifle", false);
}

void HeadHunterAim::Exit()
{
}

void HeadHunterAim::aim()
{
	mShootDelay += gDeltaTime;
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


	if (mShootCount >= 3)
	{
		mAimState = eAimState::PutBack;
		mAnimator2D->Play(L"PutBackRifle", false);
		return;
	}
	if (mShootDelay >= 0.3f)
	{
		mShootDelay = 0.f;
		mAimState = eAimState::LockOn;
		lockOnShoot();
		return;
	}	






	float deg = Rad2Deg(atan2(direction.y, direction.x));
	float armDeg = deg < 0.f ? 360.f + deg : deg;

	GameObject* hand =  mGameObject->GetComponent<HeadHunterAI>()->GetHand();
	Transform* handTransform = hand->GetComponent<Transform>();
	Vector3 handRotation = handTransform->GetRotation();

	if (mTransform->GetFlipX())
	{
		handRotation.z = 180.f - armDeg;
	}	
	else
	{
		handRotation.z = armDeg;
	}
	//handRotation.z = 180.f - armDeg;
	
	handTransform->SetRotation(handRotation);





	(void)armDeg;

	if (direction.x < 0.f)
	{
		deg = 180 - deg;

		mTransform->SetRotation(Vector3(0.f, 180.f, 0.f));

		if (armDeg < 180)
		{
			armDeg = 180.f - armDeg;
		}
		else
		{
			armDeg = 270 + 270 - armDeg;
		}

	}
	else
	{
		mTransform->SetRotation(Vector3(0.f, 0.f, 0.f));
	}

	if (armDeg < 90)
	{
		armDeg += 90.f;
	}
	else
	{
		armDeg -= 270.f;
	}

	UINT frameIdx = static_cast<UINT>(armDeg / 9.f);

	if (frameIdx >= 18)
	{
		frameIdx = 18;
	}


	mFrameIdx = frameIdx;	
}

void HeadHunterAim::rifleShoot()
{

	gSoundManager->Play(eResAudioClip::HeadHunter_groundLazer, 0.5f);

	//Shoot								
	GameObject* hand = mGameObject->GetComponent<HeadHunterAI>()->GetHand();
	GameObject* copyHand = mGameObject->GetComponent<HeadHunterAI>()->CreateHand();

	Transform* handTransform = hand->GetComponent<Transform>();
	Transform* copyHandTransform = copyHand->GetComponent<Transform>();

	copyHandTransform->SetPosition(handTransform->GetPosition());
	copyHandTransform->SetRotation(handTransform->GetRotation());
	copyHandTransform->SetScale(handTransform->GetScale());

	//Add copyHand
	mGameObject->GetGameSystem()->GetScene()->RegisterEventAddGameObject(copyHand, eLayerType::Default);
	copyHand->SetParent(mGameObject);

	GameObject* layzer = mGameObject->GetComponent<HeadHunterAI>()->CreateLazer();
	mGameObject->GetGameSystem()->GetScene()->RegisterEventAddGameObject(layzer, eLayerType::MonsterAttack);
	layzer->GetComponent<HeadHunterLazer>()->Shot(eLazerState::Shot);
	layzer->SetParent(copyHand);
}

void HeadHunterAim::lockOnShoot()
{
	//Shoot								
	gSoundManager->Play(eResAudioClip::HeadHunter_lockon, 0.5f);

	GameObject* hand = mGameObject->GetComponent<HeadHunterAI>()->GetHand();	

	//Add copyHand		
	GameObject* layzer = mGameObject->GetComponent<HeadHunterAI>()->CreateLazer();
	mGameObject->GetGameSystem()->GetScene()->RegisterEventAddGameObject(layzer, eLayerType::Default);
	layzer->GetComponent<HeadHunterLazer>()->Shot(eLazerState::LockOn);
	layzer->SetParent(hand);
}

void HeadHunterAim::EnterAim()
{
	mShootDelay = 0.f;
	mAimState = eAimState::Aim;	
}
