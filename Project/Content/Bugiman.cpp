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
	Vector4 color = GetComponent<MeshRenderer>()->GetTestColor();
	if (gInput->GetKey(eKeyCode::N))
	{
		color.w += gDeltaTime * 0.9f;
	}
	if (gInput->GetKey(eKeyCode::M))
	{
		color.w -= gDeltaTime * 0.9f;
	}
	GetComponent<MeshRenderer>()->SetTestColor(color);

	Transform* const transform = GetComponent<Transform>();	
	Vector3 scale =  transform->GetScale();
	if (gInput->GetKey(eKeyCode::NUM1))
	{
		scale.x += gDeltaTime * 0.9f;
		scale.y += gDeltaTime * 0.9f;
	}
	if (gInput->GetKey(eKeyCode::NUM2))
	{
		scale.x -= gDeltaTime * 0.9f;
		scale.y -= gDeltaTime * 0.9f;
	}
	transform->SetScale(scale);


	Vector3 rotation = transform->GetRotation();
	if (gInput->GetKeyDown(eKeyCode::NUM3))
	{
		rotation.y = 180.f;
	}	
	if (gInput->GetKeyDown(eKeyCode::NUM4))
	{
		rotation.y = 0;
	}
	transform->SetRotation(rotation);

}

void Bugiman::lateUpdate()
{
}

void Bugiman::render()
{
}
