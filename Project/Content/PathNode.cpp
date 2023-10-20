#include "pch.h"
#include "PathNode.h"
#include "Components.h"
#include <Engine/EngineMath.h>

PathNode::PathNode()
    : ScriptComponent(eScriptComponentType::PathNode)
    , mType(eLayerType::Wall)
    , mIdx(-1)
{
}

PathNode::~PathNode()
{
}

Vector2 PathNode::GetPosition() const
{
    Vector2 outMin = {};
    Vector2 outMax = {};

    //GetOwner()->GetComponent<Collider2D>()->
    Vector3 p1 = GetOwner()->GetComponent<LineCollider2D>()->GetStartPos();
    Vector3 p2 = GetOwner()->GetComponent<LineCollider2D>()->GetEndPos();
    
    helper::math::Vector2MinAndMax(Vector2(p1.x, p1.y), Vector2(p2.x, p2.y), &outMin, &outMax );

    return Vector2( (outMax.x + outMin.x) / 2.f, (outMax.y + outMin.y) / 2.f);
}

Vector3 PathNode::GetLineStartPosition() const
{
    return GetOwner()->GetComponent<LineCollider2D>()->GetStartPos();
}

Vector3 PathNode::GetLineEndPosition() const
{
    return GetOwner()->GetComponent<LineCollider2D>()->GetEndPos();
}

void PathNode::initialize()
{
}

void PathNode::update()
{
}

void PathNode::lateUpdate()
{
}
