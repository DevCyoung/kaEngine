#include "pch.h"
#include <Engine/GameObject.h>
#include <Engine/Transform.h>
#include <Engine/TimeManager.h>
#include <Engine/InputManager.h>
#include "SampleScript.h"
#include "EnumScriptComponentType.h"



using namespace engine;

SampleScript::SampleScript()
	: Script(eScriptType::Sample)
{
}

SampleScript::~SampleScript()
{
}

void SampleScript::initialize()
{
}

void SampleScript::update()
{
	
	Transform* transform = GetOwner()->GetComponent<Transform>();
	Vector3 pos = transform->GetPosition();



	if (gInput->GetKey(eKeyCode::A))
	{
		pos.x -= 1.0f * gDeltaTime;
	}
	if (gInput->GetKey(eKeyCode::D))
	{
		pos.x += 1.0f * gDeltaTime;
	}
	if (gInput->GetKey(eKeyCode::W))
	{
		pos.y += 1.0f * gDeltaTime;
	}
	if (gInput->GetKey(eKeyCode::S))
	{
		pos.y -= 1.0f * gDeltaTime;
	}

	transform->SetPosition(pos);


}

void SampleScript::lateUpdate()
{
}

void SampleScript::render()
{
}
