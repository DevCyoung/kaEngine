#include "pch.h"
#include "Bugiman.h"
#include "Components.h"
#include <Engine/TimeManager.h>
#include <Engine/InputManager.h>

Bugiman::Bugiman()
    : ScriptComponent(eScriptComponentType::Bugiman)
{
}

Bugiman::~Bugiman()
{
}

void Bugiman::initialize()
{
}

void Bugiman::update()
{
    Vector4 color = GetOwner()->GetComponent<MeshRenderer>()->GetTestColor();
    
    
    
    if (gInput->GetKey(eKeyCode::N))
    {
        color.w += gDeltaTime * 0.9f;
    }
    if (gInput->GetKey(eKeyCode::M))
    {
        color.w -= gDeltaTime * 0.9f;
    }
    
    GetOwner()->GetComponent<MeshRenderer>()->SetTestColor(color);
}

void Bugiman::lateUpdate()
{
}

void Bugiman::render()
{
}
