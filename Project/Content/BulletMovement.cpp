#include "pch.h"
#include "BulletMovement.h"
#include "Components.h"
#include <Engine/SceneManager.h>
BulletMovement::BulletMovement()
    : ScriptComponent(eScriptComponentType::BulletMovement)
	, mDelay(0.f)
{
}

BulletMovement::~BulletMovement()
{
}

void BulletMovement::initialize()
{
}

void BulletMovement::update()
{
	Transform* transform = GetComponent<Transform>();
	Vector3 pos = transform->GetPosition();

	pos += transform->GetUp() * 6000.f * gDeltaTime;
	transform->SetPosition(pos);

	mDelay += gDeltaTime;

	//SceneManager::GetInstance()->GetCurrentScene()->RegisterEventSetDestroy(GetOwner());	

	if (mDelay > 8.f)
	{
		SceneManager::GetInstance()->GetCurrentScene()->RegisterEventSetDestroy(GetOwner());
		//SceneManager::GetInstance()->GetCurrentScene()->RegisterEventSetDestroy(GetOwner());
	}
}

void BulletMovement::lateUpdate()
{
}
