#include "pch.h"
#include "CursorMovement.h"
#include "Components.h"
#include <Engine/InputManager.h>
#include <Engine/TimeManager.h>
#include <Engine/MessageManager.h>
#include <Engine/EngineMath.h>
#include <Engine/Engine.h>

CursorMovement::CursorMovement()
    : ScriptComponent(eScriptComponentType::CursorMovement)
{
}

CursorMovement::~CursorMovement()
{
}

void CursorMovement::initialize()
{
}

void CursorMovement::update()
{
	const Vector2 screenSize = gEngine->GetScreenSize();

	if (false == gInput->IsMouseHoverd(screenSize))
	{
		return;
	}

    Transform* const transform = GetComponent<Transform>();	
	Vector2 pos = helper::WindowScreenToUIPostion(gInput->GetMousePos(), screenSize);
	transform->SetPosition(Vector3(pos.x, pos.y, transform->GetPosition().z));
}

void CursorMovement::lateUpdate()
{
}

void CursorMovement::render()
{
}
