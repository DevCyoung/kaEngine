#include "pch.h"
#include "CameraInputMove.h"
#include "Components.h"
#include <Engine/InputManager.h>
#include <Engine/TimeManager.h>

CameraInputMove::CameraInputMove()
    : ScriptComponent(eScriptComponentType::CameraInputMove)
{
}

CameraInputMove::~CameraInputMove()
{
}

void CameraInputMove::initialize()
{
}

void CameraInputMove::update()
{
    Transform* const transform = GetOwner()->GetComponent<Transform>();
    Vector3 pos = transform->GetPosition();
    Vector3 dir = Vector3::Zero;

    const float cameraSpeed = 10.f;

    if(gInput->GetKey(eKeyCode::W))
    {
        dir.y += 1.f;
    }
    if (gInput->GetKey(eKeyCode::S))
    {
        dir.y += -1.f;
    }
    if (gInput->GetKey(eKeyCode::A))
    {
        dir.x -= 1.f;
    }
    if (gInput->GetKey(eKeyCode::D))
    {
        dir.x += 1.f;
    }

    dir.Normalize();    
    dir *= cameraSpeed * gDeltaTime;
    pos += dir;

    transform->SetPosition(pos);
}

void CameraInputMove::lateUpdate()
{
}

void CameraInputMove::render()
{
}
