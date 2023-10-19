#include "pch.h"
#include "HeadHunterDie.h"
#include <Engine/SceneManager.h>
#include <Engine/Scene.h>
#include "GameManager.h"
#include <Engine/AfterImage.h>
#include "KatanaZeroSystem.h"

HeadHunterDie::HeadHunterDie()
	: mState(eHeadHunterDieState::Idle)
	, mEndTime(0.f)
{
}

HeadHunterDie::~HeadHunterDie()
{
}

void HeadHunterDie::Initialize()
{
	MonsterState::Initialize();
}

void HeadHunterDie::Update()
{
	Physics2D* physics2D = mGameObject->GetGameSystem()->GetPhysics2D();
	Vector2 direction = mRigidbody2D->GetDirection();
	Vector3 position3D = mTransform->GetPosition();
	Vector2 pos = Vector2(position3D.x, position3D.y);
	RayCast2DHitInfo hitInfo = {};

	
	switch (mState)
	{
	case eHeadHunterDieState::Idle:
	{
		if (mAnimator2D->GetCurAnimationOrNull()->IsFinished())
		{
			if (physics2D->RayCastHit2D(pos, Vector2::Down, 50.f, eLayerType::Wall, &hitInfo))
			{
				//mAnimator2D->Play(L"DieLand", false);
				mState = eHeadHunterDieState::Die;
				gSoundManager->Play(eResAudioClip::HeadHunter_defeat, 0.5f);
			}
		}



	}		
		break;
	case eHeadHunterDieState::Die:
	{
		GameObject* whiteUI = mGameObject->GetGameSystem()->FindGameObject(L"BlackUI");
		GameObject* blackUI = mGameObject->GetGameSystem()->FindGameObject(L"WhiteUI");

		tSprite2DInfo colorInfo  = whiteUI->GetComponent<SpriteRenderer>()->GetSprite2DInfo();

		colorInfo.A -= gDeltaTime * 0.8f;

		whiteUI->GetComponent<SpriteRenderer>()->SetColorA(colorInfo.A);
		blackUI->GetComponent<SpriteRenderer>()->SetColorA(colorInfo.A);


		GameObject* player = GameManager::GetInstance()->GetPlayer();

		player->GetComponent<Animator2D>()->MulColorR(1.f - colorInfo.A);
		player->GetComponent<Animator2D>()->MulColorG(1.f - colorInfo.A);
		player->GetComponent<Animator2D>()->MulColorB(1.f - colorInfo.A);
		player->GetComponent<Animator2D>()->MulColorA(1.f);

		mGameObject->GetComponent<Animator2D>()->MulColorR(1.f - colorInfo.A);
		mGameObject->GetComponent<Animator2D>()->MulColorG(1.f - colorInfo.A);
		mGameObject->GetComponent<Animator2D>()->MulColorB(1.f - colorInfo.A);
		mGameObject->GetComponent<Animator2D>()->MulColorA(1.f);

		if (colorInfo.A <= 0.f)
		{
			mState = eHeadHunterDieState::End;
			TimeManager::GetInstance()->SetTileScale(1.f);
			player->GetComponent<AfterImage>()->TurnOnVisiblelity();
			mGameObject->GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::UI)->TurnOnLayer(eLayerType::UI);
			//KatanaZeroSystem::GetInstance()->LoadNextScene();
		}
	}
		break;
	case eHeadHunterDieState::End:
		mEndTime += gDeltaTime;		

		if (mEndTime >= 1.f)
		{
			mState = eHeadHunterDieState::NextScene;
			KatanaZeroSystem::GetInstance()->LoadNextScene();
		}
		break;
	default:
		break;
	}

}

void HeadHunterDie::Enter()
{
	TimeManager::GetInstance()->SetTileScale(0.3f);

	GameObject* player = GameManager::GetInstance()->GetPlayer();

	player->GetComponent<Animator2D>()->MulColorR(0.f);
	player->GetComponent<Animator2D>()->MulColorG(0.f);
	player->GetComponent<Animator2D>()->MulColorB(0.f);
	player->GetComponent<Animator2D>()->MulColorA(1.f);
	player->GetComponent<PlayerController>()->SetControl(false);

	mGameObject->GetComponent<Animator2D>()->MulColorR(0.f);
	mGameObject->GetComponent<Animator2D>()->MulColorG(0.f);
	mGameObject->GetComponent<Animator2D>()->MulColorB(0.f);
	mGameObject->GetComponent<Animator2D>()->MulColorA(1.f);

	mGameObject->GetComponent<AfterImage>()->TurnOffVisiblelity();
	player->GetComponent<AfterImage>()->TurnOffVisiblelity();

	mGameObject->GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::UI)->TurnOffLayer(eLayerType::UI);

	GameObject* whiteUI = mGameObject->GetGameSystem()->FindGameObject(L"BlackUI");
	GameObject* blackUI = mGameObject->GetGameSystem()->FindGameObject(L"WhiteUI");

	whiteUI->GetComponent<SpriteRenderer>()->TurnOnVisiblelity();
	whiteUI->GetComponent<SpriteRenderer>()->SetColorR(1.f);
	whiteUI->GetComponent<SpriteRenderer>()->SetColorG(1.f);
	whiteUI->GetComponent<SpriteRenderer>()->SetColorB(1.f);
	whiteUI->GetComponent<SpriteRenderer>()->SetColorA(1.f);

	blackUI->GetComponent<SpriteRenderer>()->TurnOnVisiblelity();
	blackUI->GetComponent<SpriteRenderer>()->SetColorR(0.f);
	blackUI->GetComponent<SpriteRenderer>()->SetColorG(0.f);
	blackUI->GetComponent<SpriteRenderer>()->SetColorB(0.f);
	blackUI->GetComponent<SpriteRenderer>()->SetColorA(1.f);

	gSoundManager->SetVolume(eResAudioClip::song_fullconfession, 0.f);	
	gSoundManager->Play(eResAudioClip::HeadHunter_Die, 0.5f);

	mAnimator2D->Play(L"DieLand", false);
}

void HeadHunterDie::Exit()
{
}
