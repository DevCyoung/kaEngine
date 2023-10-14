#include "pch.h"
#include "BulletMovement.h"
#include "Components.h"
#include <Engine/SceneManager.h>
#include <Engine/Color.h>
#include <Engine/EngineMath.h>
#include "GameManager.h"
#include "FolowPlayer.h"
#include "DoorController.h"
#include "BasicMonsterAI.h"

BulletMovement::BulletMovement()
    : ScriptComponent(eScriptComponentType::BulletMovement)
	, mDelay(0.f)
	, mDir{}
	, mSpeed(1700.f)
	, mbPlayerBullet(false)
	, mbScaleMode(true)
	, mbRotationMode(false)
	, mBulletType(eBulletType::MonsterBullet)
{
}

BulletMovement::~BulletMovement()
{
}

void BulletMovement::onCollisionEnter(Collider2D* other)
{
	(void)other;
	//

	/*if (GetOwner()->GetState() == GameObject::eState::Destroy)
	{
		return;
	}
	
	gCurrentScene->RegisterEventSetDestroy(GetOwner());*/

	eLayerType otherLayer = other->GetOwner()->GetLayer();

	if (otherLayer == eLayerType::PlayerAttack && false == mbPlayerBullet)
	{
		mbPlayerBullet = true;
		gSoundManager->Play(eResAudioClip::slashBullet, 1.f);

		mDir.x *= -1.f;
		mDir.y *= -1.f;

		mSpeed *= 1.5f;


		Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();

		gEffectManager->Shot(L"SpinerBullet", position);

		Camera* const camera = GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::Main);
		camera->GetOwner()->GetComponent<FolowPlayer>()->ShakeCamera();
	}
	else if (otherLayer == eLayerType::Door && other->GetOwner()->GetComponent<DoorController>()->IsOpen())
	{	
		return;
	}
	else if (otherLayer == eLayerType::Wall || 	
		otherLayer == eLayerType::Door||
		otherLayer == eLayerType::LeftSlope ||
		otherLayer == eLayerType::RightSlope ||
		(otherLayer == eLayerType::Monster && 
			mbPlayerBullet && 
			false == other->GetOwner()->GetComponentOrNull<BasicMonsterAI>()->IsDead())  )
	{		
		GetOwner()->GetComponent<Transform>()->SetPosition(10000000.f, 10000000.f, 0.f);

		if (mBulletType == eBulletType::MonsterBullet || 
			mBulletType == eBulletType::PlayerBullet)
		{
			gSoundManager->Play(eResAudioClip::bulletHit1, 0.3f);			
		}
		else if (mBulletType == eBulletType::PlayerBeer1 || 
			mBulletType == eBulletType::PlayerBeer2)
		{	
			gSoundManager->Play(eResAudioClip::glassbreak, 0.7f);
		}		
	}	
}

void BulletMovement::onCollisionStay(Collider2D* other)
{
	(void)other;
}

void BulletMovement::onCollisionExit(Collider2D* other)
{
	(void)other;
}

void BulletMovement::initialize()
{
}

void BulletMovement::update()
{
	Transform* transform = GetOwner()->GetComponent<Transform>();
	Vector3 pos = transform->GetPosition();
	
	pos += mDir * mSpeed * gDeltaTime;
	transform->SetPosition(pos);
	//
	mDelay += gDeltaTime;

	
	
	//if (mDelay > 18.f)
	//{
	//	if (GetOwner()->GetState() != GameObject::eState::Destroy)
	//	{
	//		gCurrentScene->RegisterEventSetDestroy(GetOwner());
	//	}		
	//}

	float deg = Rad2Deg(atan2(mDir.y, mDir.x));
	if (mDir.x < 0.f)
	{
		//deg = 180 - deg;
	}

	Vector3 rotation = GetOwner()->GetComponent<Transform>()->GetRotation();

	if (mbScaleMode)
	{
		rotation.z = deg;

		//GetOwner()->GetComponent<Transform>()->SetRotation(0.f, 0.f, deg);

		float timeScale = TimeManager::GetInstance()->GetTileScale();

		Vector3 scale = GetOwner()->GetComponent<Transform>()->GetScale();

		//default 0.2f;
		scale.x = timeScale;
		GetOwner()->GetComponent<Transform>()->SetScale(scale);
	}	

	if (mbRotationMode)
	{
		rotation.z += 360.f * 3.f * gDeltaTime;
	}


	GetOwner()->GetComponent<Transform>()->SetRotation(rotation);
}

void BulletMovement::lateUpdate()
{
}
