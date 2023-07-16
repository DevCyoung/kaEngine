#include "pch.h"
#include "BulletMovement.h"
#include "Components.h"
#include <Engine/SceneManager.h>
BulletMovement::BulletMovement()
    : ScriptComponent(eScriptComponentType::BulletMovement)
	, mDelay(0.f)
	, mDir{}
{
}

BulletMovement::~BulletMovement()
{
}

void BulletMovement::OnCollisionEnter(Collider2D* other)
{
	(void)other;
	//
	if (GetOwner()->GetState() == GameObject::eState::Destroy)
	{
		return;
	}
	
	gCurrentScene->RegisterEventSetDestroy(GetOwner());
}

void BulletMovement::OnCollisionStay(Collider2D* other)
{
	(void)other;
}

void BulletMovement::OnCollisionExit(Collider2D* other)
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
	
	pos += mDir * 30.f * gDeltaTime;
	transform->SetPosition(pos);
	//
	mDelay += gDeltaTime;
	
	if (mDelay > 18.f)
	{
		if (GetOwner()->GetState() != GameObject::eState::Destroy)
		{
			gCurrentScene->RegisterEventSetDestroy(GetOwner());
		}
		
	}
}

void BulletMovement::lateUpdate()
{
}
