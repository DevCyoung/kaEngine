#include "pch.h"
#include "PlayerMovementTest.h"
#include "Components.h"

#include "BulletMovement.h"
#include "GameObjectBuilder.h"

#include <Engine/SceneManager.h>

PlayerMovementTest::PlayerMovementTest()
    : ScriptComponent(eScriptComponentType::PlayerMovementTest)
{
}

PlayerMovementTest::~PlayerMovementTest()
{
}

void PlayerMovementTest::initialize()
{
}

void PlayerMovementTest::update()
{
    Transform* transform = GetComponent<Transform>();

    Vector3 pos = transform->GetPosition();
    Vector3 dir = Vector3::Zero;

    if (gInput->GetKey(eKeyCode::UP))
    {
        dir.y += 1.f;
    }

    if (gInput->GetKey(eKeyCode::DOWN))
    {
        dir.y -= 1.f;
    }

    if (gInput->GetKey(eKeyCode::LEFT))
    {
        dir.x -= 1.f;
    }

    if (gInput->GetKey(eKeyCode::RIGHT))
    {
        dir.x += 1.f;
    }

    dir.Normalize();

    pos += dir * gDeltaTime * 600.f;

    transform->SetPosition(pos);


    static float angle = 0.f;
    angle += gDeltaTime * 300.f;

    //if (gInput->GetKey(eKeyCode::K))
    //{
    //    
    //}
    //if (gInput->GetKey(eKeyCode::L))
    //{
    //    angle -= gDeltaTime * 100.f;
    //}

    pos.y += 200.f;

    for (int i = 0; i < 16; ++i)
    {
        GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"Door");

        obj->AddComponent<BulletMovement>();

        obj->GetComponent<Transform>()->SetScale(0.25f, 0.25f, 1.f);
        obj->GetComponent<Transform>()->SetRotation(0.f, 0.f, i * 8 + angle);
        obj->GetComponent<Transform>()->SetPosition(pos);

        gCurrentScene->RegisterEventAddGameObject(obj, eLayerType::Default);  
    }

}

void PlayerMovementTest::lateUpdate()
{
}
