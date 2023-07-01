#include "pch.h"
#include "CameraInputMove.h"
#include "Components.h"
#include <Engine/InputManager.h>
#include <Engine/TimeManager.h>
#include <Engine/ConstantBuffer.h>
#include <Engine/CBCollection.h>
#include <Engine/MessageManager.h>
#include <Engine/Camera.h>
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
    Camera* const camera = GetComponent<Camera>();

    if (gInput->GetKeyDown(eKeyCode::F1))
    {        
        camera->SetProjectiontType(Camera::eProjectionType::Orthographic);
	}
    else if (gInput->GetKeyDown(eKeyCode::F2))
    {        
        camera->SetProjectiontType(Camera::eProjectionType::Perspective);
    }
	
    
    Transform* const transform = GetComponent<Transform>();
    Vector3 pos = transform->GetPosition();
    Vector3 dir = Vector3::Zero;

    

    if (camera->GetProjectiontType() == Camera::eProjectionType::Perspective)
    {
        constexpr float cameraSpeed = 600.f;

        Vector3 vPos    = transform->GetPosition();
        Vector3 vRot    = transform->GetRotation();

        Vector3 vForward = transform->GetForward();        
        Vector3 vRight = transform->GetRight();        

        if (gInput->GetKey(eKeyCode::W))
        {
            vPos += gDeltaTime * vForward * cameraSpeed;
        }

        if (gInput->GetKey(eKeyCode::S))
        {
            vPos -= gDeltaTime * vForward * cameraSpeed;
        }

        if (gInput->GetKey(eKeyCode::D))
        {
            vPos += gDeltaTime * vRight * cameraSpeed;
        }

        if (gInput->GetKey(eKeyCode::A))
        {
            vPos -= gDeltaTime * vRight * cameraSpeed;
        }

        if (gInput->GetKey(eKeyCode::RBUTTON))
        {
            Vector2 vMouseDir = gInput->GetMouseDir();
            vMouseDir.Normalize();
            vRot.y += gDeltaTime * vMouseDir.x * 180.f;
            vRot.x -= gDeltaTime * vMouseDir.y * 180.f;
        }

        transform->SetPosition(vPos);
        transform->SetRotation(vRot);
    }
    else
    {
        constexpr float cameraSpeed = 600.f;        

        if (gInput->GetKey(eKeyCode::W))
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

}

void CameraInputMove::lateUpdate()
{
}

void CameraInputMove::render()
{
}
