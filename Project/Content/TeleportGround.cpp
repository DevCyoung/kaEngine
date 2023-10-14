#include "pch.h"
#include "TeleportGround.h"
#include "GameManager.h"
#include "HeadHunterAI.h"
#include "HeadHunterLazer.h"

TeleportGround::TeleportGround()
	:mTelportGroundState(eTeleportGroundState::None)
{
}

TeleportGround::~TeleportGround()
{
}

void TeleportGround::Initialize()
{
	MonsterState::Initialize();
}

void TeleportGround::Update()
{
	switch (mTelportGroundState)
	{
	case eTeleportGroundState::None:
		break;
	case eTeleportGroundState::In:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			mTelportGroundState = eTeleportGroundState::Out;
			mAnimator2D->Play(L"TeleportOutGround", false);
		}
		break;
	case eTeleportGroundState::Out:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{	
			mTelportGroundState = eTeleportGroundState::WallIn;
			mAnimator2D->Play(L"TeleportIn", false);

			mTransform->SetPosition(-500, 0, 0.f);
			mTransform->SetFlipx(false);
			mRigidbody2D->TurnOffGravity();	
		}
		break;
	case eTeleportGroundState::WallIn:
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			GetMonsterFSM()->ChangeState(HeadHunterAI::WallJump);
		}
		break;	
	default:
		break;
	}
}

void TeleportGround::Enter()
{	
	mTelportGroundState = eTeleportGroundState::In;
	mTransform->SetPosition(400, -250, 0.f);
	mTransform->SetFlipx(true);
	mAnimator2D->Play(L"TeleportInGround", false);
	
	gSoundManager->Play(eResAudioClip::HeadHunter_lockon, 1.f);
	Shot();
}

void TeleportGround::Exit()
{
}

void TeleportGround::Shot()
{	
	//Shoot								
	//GameObject* hand = mGameObject->GetComponent<HeadHunterAI>()->GetHand();
	GameObject* copyHand = mGameObject->GetComponent<HeadHunterAI>()->CreateHand();
	copyHand->SetParent(nullptr);

	//Transform* handTransform = hand->GetComponent<Transform>();
	Transform* copyHandTransform = copyHand->GetComponent<Transform>();

	Vector3 position = mTransform->GetPosition();
	Vector3 copyHandPosition = position;

	position.x += 2.f;
	position.y += 22.f;

	copyHandTransform->SetPosition(position);
	copyHandTransform->SetFlipx(true);
	copyHandTransform->SetScale(2.f, 2.f, 1.f);

	//Add copyHand

	mGameObject->GetGameSystem()->GetScene()->RegisterEventAddGameObject(copyHand, eLayerType::Default);
	//copyHand->SetParent(mGameObject);

	GameObject* layzer = mGameObject->GetComponent<HeadHunterAI>()->CreateLazer();
	mGameObject->GetGameSystem()->GetScene()->RegisterEventAddGameObject(layzer, eLayerType::MonsterAttack);
	layzer->GetComponent<HeadHunterLazer>()->Shot(eLazerState::InAndOutLockOn);
	layzer->SetParent(copyHand);
}
