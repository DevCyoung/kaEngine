#include "pch.h"
#include "RewindComponent.h"
#include "Components.h"
#include "GameManager.h"

RewindComponent::RewindComponent()
    : ScriptComponent(eScriptComponentType::RewindComponent)
{
}

RewindComponent::~RewindComponent()
{
}

void RewindComponent::initialize()
{
    GameManager::GetInstance()->GetRewindManager()->RegisterRewindObject(GetOwner());
}

void RewindComponent::update()
{
}

void RewindComponent::lateUpdate()
{
}
