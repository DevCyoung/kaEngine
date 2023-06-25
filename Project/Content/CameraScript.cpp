#include "pch.h"
#include <Engine/GameObject.h>
#include <Engine/Transform.h>
#include <Engine/TimeManager.h>
#include <Engine/InputManager.h>
#include "CameraScript.h"
#include "EnumScript.h"

using namespace engine;

CameraScript::CameraScript()
	: Script(eScriptType::CameraScript)
{

}

CameraScript::~CameraScript()
{
}

void CameraScript::initialize()
{
	
}

void CameraScript::update()
{
	GetComponentName(eComponentType::Camera);
	CreateComponentByEnum(eComponentType::Camera);
	CreateComponentByName(L"Camera");

	Transform* transform = GetOwner()->GetComponent<Transform>();
	Vector3 pos = transform->GetPosition();

	
	
	if (gInput->GetKey(eKeyCode::A))
	{
		pos.x -= 10.0f * gDeltaTime;
	}
	if (gInput->GetKey(eKeyCode::D))
	{
		pos.x += 10.0f * gDeltaTime;
	}
	if (gInput->GetKey(eKeyCode::W))
	{
		pos.y += 10.0f * gDeltaTime;
	}
	if (gInput->GetKey(eKeyCode::S))
	{
		pos.y -= 10.0f * gDeltaTime;
	}
	if (gInput->GetKey(eKeyCode::Q))
	{
		pos.z -= 10.0f * gDeltaTime;
	}
	if (gInput->GetKey(eKeyCode::E))
	{
		pos.z += 10.0f * gDeltaTime;
	}

	if (gInput->GetKey(eKeyCode::SPACE))
	{
		Vector3 rot = transform->GetRotation();
		rot.z += 1.0f * gDeltaTime;
		transform->SetRotation(rot);
	}
	transform->SetPosition(pos);
}

void CameraScript::lateUpdate()
{
}

void CameraScript::render()
{
}

