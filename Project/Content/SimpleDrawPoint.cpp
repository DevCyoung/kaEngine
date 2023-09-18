#include "pch.h"
#include "SimpleDrawPoint.h"
#include "Components.h"
#include <Engine/Color.h>
#include "GameManager.h"
#include <Engine/EngineMath.h>

SimpleDrawPoint::SimpleDrawPoint()
    : ScriptComponent(eScriptComponentType::SimpleDrawPoint)
{
}

SimpleDrawPoint::~SimpleDrawPoint()
{
}

void SimpleDrawPoint::initialize()
{
}

void SimpleDrawPoint::update()
{   

    


}

void SimpleDrawPoint::lateUpdate()
{
    RenderTargetRenderer* const renderTargetRenderer = GetOwner()->GetGameSystem()->GetRenderTargetRenderer();
    DebugRenderer2D* const debugRender2D = renderTargetRenderer->GetDebugRenderer2D();

    Vector3 pos = GetOwner()->GetComponent<Transform>()->GetWorldMatrix().Translation();
    debugRender2D->DrawFillCircle2D(pos, 2.5f, 0.f, helper::Color::YELLOW);

    //Raycast
    RayCast2DHitInfo hitInfo;

    //const float rayDistance = 300.f;    

    GameObject* player =  GameManager::GetInstance()->GetPlayer();    
    Vector2 direction =  helper::math::GetDirection2D(this->GetOwner(), player);
    float distance = helper::math::GetDistance2D(this->GetOwner(), player);

    //°¢µµ
    //float angle = helper::math::GetAngle2D(this->GetOwner(), player);
    //¿ÞÂÊ

    float deg = Rad2Deg(atan2(direction.y, direction.x));
    if (direction.x < 0.f)
    {
        deg = 180 - deg;

        origin->GetComponent<Transform>()->SetRotation(Vector3(0.f, 180.f, 0.f));
    }
    else
    {
        origin->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, 0.f));
    }

    GetOwner()->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, deg));

    Vector2 pos2D = Vector2(pos.x, pos.y);    

    

    
    Physics2D* const physics2D = GetOwner()->GetGameSystem()->GetPhysics2D();

    if (false == physics2D->RayCastHit2D(pos2D, direction, distance, eLayerType::Wall, &hitInfo) && 
        false == physics2D->RayCastHit2D(pos2D, direction, distance, eLayerType::LeftSlope, &hitInfo) &&
        false == physics2D->RayCastHit2D(pos2D, direction, distance, eLayerType::RightSlope, &hitInfo) )
    {
        debugRender2D->DrawLine2D2(pos, direction, distance, 0.f, helper::Color::MAGENTA);
	}
    else
    {
        debugRender2D->DrawLine2D2(pos, direction, distance, 0.f, helper::Color::YELLOW);
    }

}
