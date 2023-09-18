#include "pch.h"
#include "PlayerPath.h"
#include "Components.h"


PlayerPath::PlayerPath()
    : ScriptComponent(eScriptComponentType::PlayerPath)
    , mCurPathNode(nullptr)
{
}

PlayerPath::~PlayerPath()
{
}

void PlayerPath::initialize()
{
}

void PlayerPath::update()
{    
}

void PlayerPath::lateUpdate()
{
    Physics2D* const physics2D = GetOwner()->GetGameSystem()->GetPhysics2D();

    RayCast2DHitInfo hitInfo = {};

    Vector3 pos = GetOwner()->GetComponent<Transform>()->GetWorldMatrix().Translation();

    Vector2 pos2D = Vector2(pos.x, pos.y);

    float distance = 2000.f;

    if (physics2D->RayCastHit2D(pos2D, Vector2::Down, distance, eLayerType::PathNode, &hitInfo))
    {
        mCurPathNode = hitInfo.collider->GetOwner()->GetComponent<PathNode>();  
    }
}
