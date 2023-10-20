#include "pch.h"
#include "SlashEffectMovement.h"
#include "Components.h"
#include <Engine/EngineMath.h>

SlashEffectMovement::SlashEffectMovement()
    : ScriptComponent(eScriptComponentType::SlashEffectMovement)
{
}

SlashEffectMovement::~SlashEffectMovement()
{
}

void SlashEffectMovement::initialize()
{
}

void SlashEffectMovement::update()
{
    int rand = helper::rand::RandInt(1, 10000) % 2;

    if (rand == 0)
    {
        GetOwner()->GetComponent<SpriteRenderer>()->SetColorR(0.31f);
        GetOwner()->GetComponent<SpriteRenderer>()->SetColorG(1.f);
        GetOwner()->GetComponent<SpriteRenderer>()->SetColorB(1.f);
        GetOwner()->GetComponent<SpriteRenderer>()->SetColorA(0.5f);
    }
    else
    {
        GetOwner()->GetComponent<SpriteRenderer>()->SetColorR(0.92f);
        GetOwner()->GetComponent<SpriteRenderer>()->SetColorG(0.14f);
        GetOwner()->GetComponent<SpriteRenderer>()->SetColorB(0.72f);
        GetOwner()->GetComponent<SpriteRenderer>()->SetColorA(0.5f);
    }    

    Vector3 direction = GetOwner()->GetComponent<Transform>()->GetRight();
    Vector3 position = GetOwner()->GetComponent<Transform>()->GetPosition();

    position.x += direction.x * 80000.f * gDeltaTime;
    position.y += direction.y * 80000.f * gDeltaTime;
    GetOwner()->GetComponent<Transform>()->SetPosition(position);
}

void SlashEffectMovement::lateUpdate()
{
}
