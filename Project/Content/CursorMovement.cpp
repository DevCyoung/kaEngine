#include "pch.h"
#include "CursorMovement.h"
#include "Components.h"
#include <Engine/InputManager.h>
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
    Vector2 screenMousePos = gInput->GetMousePos();
    Vector2 screenSize = 
    { 
        static_cast<float>(gEngine->GetScreenWidth()),
        static_cast<float>(gEngine->GetScreenHeight())
    };
    Vector2 UIPos = helper::ScreenToUIPostion(screenMousePos, screenSize);
    Transform* const transform = GetComponent<Transform>();
    transform->SetPosition({ UIPos.x, UIPos.y, 0.f });
}

void CursorMovement::lateUpdate()
{
}

void CursorMovement::render()
{
}
