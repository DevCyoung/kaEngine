#include "pch.h"
#include "RewindComponent.h"
#include "Components.h"
#include "GameManager.h"
#include <Engine/AfterImage.h>

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
    AfterImage* afterImage =  GetOwner()->GetComponentOrNull<AfterImage>();

    if (nullptr != afterImage)
    {
        eRewindState state =  GameManager::GetInstance()->GetRewindManager()->GetRewindState();

        if (state == eRewindState::Rewind)
        {
            afterImage->TurnOffVisiblelity();
		}        

    }

}

void RewindComponent::lateUpdate()
{
}
