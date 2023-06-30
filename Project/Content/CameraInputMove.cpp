#include "pch.h"
#include "CameraInputMove.h"
#include "Components.h"
#include <Engine/InputManager.h>
#include <Engine/TimeManager.h>
#include <Engine/ConstantBuffer.h>
#include <Engine/CBCollection.h>
#include <Engine/MessageManager.h>
#include "Bugiman.h"

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
    Transform* const transform = GetComponent<Transform>();
    Vector3 pos = transform->GetPosition();
    Vector3 dir = Vector3::Zero;    

    constexpr float cameraSpeed = 10.f;

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

    wchar_t buffer[256] = { 0, };
    swprintf_s(buffer, 50, L"<Camera Position : %.2f, %.2f, %.2f>", pos.x, pos.y, pos.z);
    gMessageManager->AddMessage(buffer);    
}

void CameraInputMove::lateUpdate()
{
}

void CameraInputMove::render()
{
}
