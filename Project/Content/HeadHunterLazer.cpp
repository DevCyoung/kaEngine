#include "pch.h"
#include "HeadHunterLazer.h"
#include "Components.h"
#include <Engine/Scene.h>
#include <Engine/EngineMath.h>
#include "MonsterAttack.h"
#include "GameManager.h"
#include "FolowPlayer.h"
HeadHunterLazer::HeadHunterLazer()
	: ScriptComponent(eScriptComponentType::HeadHunterLazer)
	, mbShoot(false)
	, mbLazerOn(false)
	, mState(eLazerState::None)
	, mInTime(0.f)
	, mUpdateCount(0)
{
}

HeadHunterLazer::~HeadHunterLazer()
{
}

void HeadHunterLazer::initialize()
{
}

void HeadHunterLazer::update()
{
	++mUpdateCount;


	if (mUpdateCount == 2)
	{
		GetOwner()->GetComponent<SpriteRenderer>()->TurnOnVisiblelity();
	}

	switch (mState)
	{
	case eLazerState::None:
		break;
	case eLazerState::Shot:
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();

		Vector3 scale = transform->GetScale();
		scale.y -= gDeltaTime * 4.f;
		transform->SetScale(scale);

		if (scale.y < 0.35f)
		{
			GetOwner()->GetComponent<MonsterAttack>()->SetAttackAble(false);
		}

		if (scale.y < 0.01f)
		{
			GetOwner()->GetGameSystem()->GetScene()->RegisterEventSetDestroy(GetOwner());
		}

		SpriteRenderer* spriteRenderer = GetOwner()->GetComponent<SpriteRenderer>();

		//Vector4 color = Vector4::One;

		int rand = helper::rand::RandInt(0, 100000) % 2;

		if (rand == 0)
		{
			rand = helper::rand::RandInt(-10, 10) % 10;

			spriteRenderer->SetColorR((226 + rand) / 255.f);
			spriteRenderer->SetColorG((148 + rand) / 255.f);
			spriteRenderer->SetColorB((66 + rand) / 255.f);
			spriteRenderer->SetColorA(255 / 255.f);
		}
		else
		{
			rand = helper::rand::RandInt(-10, 10) % 10;

			spriteRenderer->SetColorR((255 - rand) / 255.f);
			spriteRenderer->SetColorG((255 - rand) / 255.f);
			spriteRenderer->SetColorB((255 - rand) / 255.f);
			spriteRenderer->SetColorA(255 / 255.f);
		}

	}
	break;
	case eLazerState::LockOn:
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();

		Vector3 scale = transform->GetScale();
		scale.y -= gDeltaTime * 0.5f;
		transform->SetScale(scale);

	

		if (scale.y < 0.01f)
		{
			GetOwner()->GetGameSystem()->GetScene()->RegisterEventSetDestroy(GetOwner());			
		}

		SpriteRenderer* spriteRenderer = GetOwner()->GetComponent<SpriteRenderer>();
		spriteRenderer->SetColorR(1.f);
		spriteRenderer->SetColorG(1.f);
		spriteRenderer->SetColorB(0.f);
		spriteRenderer->SetColorA(1.f);
	}
	break;

	case eLazerState::InAndOutLockOn:
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();

		Vector3 scale = transform->GetScale();
		scale.y -= gDeltaTime * 0.5f;
		transform->SetScale(scale);
	

		SpriteRenderer* spriteRenderer = GetOwner()->GetComponent<SpriteRenderer>();

		if (scale.y < 0.001f)
		{
			//GetOwner()->GetGameSystem()->GetScene()->RegisterEventSetDestroy(GetOwner());
			//spriteRenderer->TurnOffVisiblelity();
			mState = eLazerState::InAndOut_IN;
			scale.y = 1.f;

			//Camera* const mainCamera = GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::Main);
			//mainCamera->GetOwner()->GetComponent<FolowPlayer>()->ShakeCamera();
			//GameManager::GetInstance()->GetEventManager()->ShotTimeEffect(0.1f, 0.2f, eTimeEffectType::Damaged);

			transform->SetScale(scale);
			mInTime = 0.f;
			GetOwner()->GetComponent<MonsterAttack>()->SetAttackAble(true);

			gSoundManager->Play(eResAudioClip::HeadHunter_groundLazer, 0.5f);
			return;
		}

		
		spriteRenderer->SetColorR(1.f);
		spriteRenderer->SetColorG(1.f);
		spriteRenderer->SetColorB(0.f);
		spriteRenderer->SetColorA(1.f);
	}
		break;
	case eLazerState::InAndOut_IN:
	{
		mInTime += gDeltaTime;

		Transform* transform = GetOwner()->GetComponent<Transform>();
		SpriteRenderer* spriteRenderer = GetOwner()->GetComponent<SpriteRenderer>();

		Vector3 scale = transform->GetScale();

		if (false == mbLazerOn)
		{
			scale.y -= gDeltaTime * 4.5f;
			transform->SetScale(scale);
		}

		if (scale.y < 0.2f)
		{
			GetOwner()->GetComponent<MonsterAttack>()->SetAttackAble(false);			
		}
		

		if (scale.y < 0.01f)
		{
			GetOwner()->GetGameSystem()->GetScene()->RegisterEventSetDestroy(GetOwner());
			spriteRenderer->TurnOffVisiblelity();
			mState = eLazerState::InAndOut_OUT;
			return;
		}

		//Vector4 color = Vector4::One;

		int rand = helper::rand::RandInt(0, 1000000) % 2;
		if (rand == 0)
		{
			rand = helper::rand::RandInt(-10, 10) % 10;

			spriteRenderer->SetColorR((226 + rand) / 255.f);
			spriteRenderer->SetColorG((148 + rand) / 255.f);
			spriteRenderer->SetColorB((66 + rand) / 255.f);
			spriteRenderer->SetColorA(255 / 255.f);
		}
		else
		{
			rand = helper::rand::RandInt(-10, 10) % 10;

			spriteRenderer->SetColorR((255 - rand) / 255.f);
			spriteRenderer->SetColorG((255 - rand) / 255.f);
			spriteRenderer->SetColorB((255 - rand) / 255.f);
			spriteRenderer->SetColorA(255 / 255.f);
		}
	}
	break;
	case eLazerState::InAndOut_OUT:
	{
	}
		break;
	default:
		break;
	}
}

void HeadHunterLazer::lateUpdate()
{
	//Transform* transform = GetOwner()->GetComponent<Transform>();



	//GetOwner()->SetParent(nullptr);
}

void HeadHunterLazer::Shot()
{
	mbShoot = true;
}

void HeadHunterLazer::LockOnShot()
{
	Transform* transform = GetOwner()->GetComponent<Transform>();

	Vector3 scale = transform->GetScale();
	scale.y = 0.2f;
	transform->SetScale(scale);
}

void HeadHunterLazer::Shot(eLazerState state)
{
	mState = state;
	GetOwner()->GetComponent<MonsterAttack>()->SetAttackAble(false);

	switch (mState)
	{
	case eLazerState::None:
		break;
	case eLazerState::Shot:
		Shot();
		GetOwner()->GetComponent<MonsterAttack>()->SetAttackAble(true);
		break;
	case eLazerState::LockOn:
		LockOnShot();
		break;
	case eLazerState::InAndOutLockOn:
		LockOnShot();
		mInTime = 0.f;
		break;
	case eLazerState::InAndOut_IN:
		break;
	case eLazerState::InAndOut_OUT:
		break;
	default:
		break;
	}
}
