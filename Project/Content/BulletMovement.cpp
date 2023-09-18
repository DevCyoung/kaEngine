#include "pch.h"
#include "BulletMovement.h"
#include "Components.h"
#include <Engine/SceneManager.h>
#include <Engine/Color.h>
#include <Engine/EngineMath.h>
BulletMovement::BulletMovement()
    : ScriptComponent(eScriptComponentType::BulletMovement)
	, mDelay(0.f)
	, mDir{}
{
}

BulletMovement::~BulletMovement()
{
}

void BulletMovement::onCollisionEnter(Collider2D* other)
{
	(void)other;
	//
	if (GetOwner()->GetState() == GameObject::eState::Destroy)
	{
		return;
	}
	
	gCurrentScene->RegisterEventSetDestroy(GetOwner());
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
	
	pos += mDir * 800.f * gDeltaTime;
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

	GetOwner()->GetComponent<Transform>()->SetRotation(0.f, 0.f, deg);

}

void BulletMovement::lateUpdate()
{
}
