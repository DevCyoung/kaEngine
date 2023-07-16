#include "pch.h"
#include "PlayerMovementTest.h"
#include "Components.h"

#include "BulletMovement.h"
#include "GameObjectBuilder.h"

#include <Engine/SceneManager.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>

PlayerMovementTest::PlayerMovementTest()
    : ScriptComponent(eScriptComponentType::PlayerMovementTest)
    , mbRight(true)
    , angle(0.f)
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
    Transform* transform = GetOwner()->GetComponent<Transform>();

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
    pos += dir * gDeltaTime * 100.f;
    transform->SetPosition(pos);


    

    if (mbRight)
    {
        angle += gDeltaTime * 10.f;
    }
    else
    {
        angle -= gDeltaTime * 10.f;
    }

    transform->SetRotation(0.f, 0.f, angle);
}

void PlayerMovementTest::lateUpdate()
{
}
