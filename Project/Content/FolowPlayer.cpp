#include "pch.h"
#include "FolowPlayer.h"
#include "Components.h"

FolowPlayer::FolowPlayer()
    : ScriptComponent(eScriptComponentType::FolowPlayer)
    , mPlayerTransform(nullptr)
{
}

FolowPlayer::~FolowPlayer()
{
}

void FolowPlayer::initialize()
{
    mPlayerTransform = GetOwner()->GetGameSystem()->FindGameObject(L"Player")->GetComponent<Transform>();
}

void FolowPlayer::update()
{   

}

void FolowPlayer::fixedUpdate()
{
    //RenderTargetRenderer* const renderer = GetOwner()->GetGameSystem()->GetRenderTargetRenderer();
    //DebugRenderer2D* const debugRenderer = renderer->GetDebugRenderer2D();

    //Vector3  cameraPos3D = GetOwner()->GetComponent<Transform>()->GetPosition();
    //Vector3  playerPos3D = mPlayerTransform->GetPosition();

    //Vector3 cameraToPlayer = playerPos3D - cameraPos3D;
    //cameraToPlayer.z = 0.f;

    //Camera* const camera = GetOwner()->GetComponent<Camera>();
    //Physics2D* const physics2D = GetOwner()->GetGameSystem()->GetPhysics2D();
    //Vector2 camRTSize = camera->GetRenderTargetSize();

    ////camera2D
    //Vector2 cameraPos2D = Vector2(cameraPos3D.x, cameraPos3D.y);    

    //RayCast2DHitInfo hitInfo;

    //debugRenderer->DrawLine2D2(cameraPos3D, Vector2::Down, camRTSize.y / 2.f, 0.f, Vector4(1.f, 0.f, 0.f, 1.f));
    //if (physics2D->RayCastHit2D(cameraPos2D, Vector2::Down, camRTSize.y / 2.f, eLayerType::CamearaWall, &hitInfo))
    //{
    //    cameraPos3D.y += hitInfo.hitPos.y;
    //    GetOwner()->GetComponent<Transform>()->SetPosition(cameraPos3D);
    //}    


    //if (cameraToPlayer.Length() <= 100.f)
    //{
    //    return;
    //}
    //cameraToPlayer.Normalize();

    //


    //
    //cameraPos3D += cameraToPlayer * 500.f * gDeltaTime;

    //GetOwner()->GetComponent<Transform>()->SetPosition(cameraPos3D);
}


void FolowPlayer::lateUpdate()
{    //Camera* const camera = GetOwner()->GetComponent<Camera>();


}

void FolowPlayer::lastUpdate()
{
  
}
