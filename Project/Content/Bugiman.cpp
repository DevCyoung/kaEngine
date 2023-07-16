#include "pch.h"
#include "Bugiman.h"
#include "Components.h"
#include <Engine/TimeManager.h>
#include <Engine/InputManager.h>
#include <Engine/EngineMath.h>

Bugiman::Bugiman()
	: ScriptComponent(eScriptComponentType::Bugiman)
{
}

Bugiman::~Bugiman()
{
}

void Bugiman::initialize()
{
}

void Bugiman::update()
{
	Vector4 color = GetOwner()->GetComponent<SpriteRenderer>()->GetTestColor();
	if (gInput->GetKey(eKeyCode::N))
	{
		color.w += gDeltaTime * 0.9f;
	}
	if (gInput->GetKey(eKeyCode::M))
	{
		color.w -= gDeltaTime * 0.9f;
	}
	GetOwner()->GetComponent<SpriteRenderer>()->SetTestColor(color);

	Transform* const transform = GetOwner()->GetComponent<Transform>();
	Vector3 scale =  transform->GetScale();
	if (gInput->GetKey(eKeyCode::NUMPAD1))
	{
		scale.x += gDeltaTime * 0.9f;
		scale.y += gDeltaTime * 0.9f;
	}
	if (gInput->GetKey(eKeyCode::NUMPAD2))
	{
		scale.x -= gDeltaTime * 0.9f;
		scale.y -= gDeltaTime * 0.9f;
	}
	transform->SetScale(scale);


	Vector3 rotation = transform->GetRotation();
	if (gInput->GetKeyDown(eKeyCode::NUMPAD4))
	{
		rotation.y = 180.f;
	}	
	if (gInput->GetKeyDown(eKeyCode::NUMPAD5))
	{
		rotation.y = 0;
	}
	
	if (gInput->GetKey(eKeyCode::NUMPAD7))
	{
		rotation.z += gDeltaTime * 30.f;
	}
	if (gInput->GetKey(eKeyCode::NUMPAD8))
	{
		rotation.z -= gDeltaTime * 30.f;
	}
	transform->SetRotation(rotation);

}

void Bugiman::lateUpdate()
{
}

