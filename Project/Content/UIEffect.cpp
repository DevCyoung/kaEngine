#include "pch.h"
#include "UIEffect.h"
#include "Components.h"
#include <Engine/TimeManager.h>

UIEffect::UIEffect()
    : ScriptComponent(eScriptComponentType::UIEffect)
    , x(1.f)
{    
}

UIEffect::~UIEffect()
{
}

void UIEffect::initialize()
{
}

void UIEffect::update()
{
    MeshRenderer* meshRenderer = GetComponent<MeshRenderer>();

    meshRenderer->bColorInfo = 1;
    meshRenderer->testX.x -= gDeltaTime * 0.05f;
    meshRenderer->testX.y  = gGlobalTime * 10.f;
}

void UIEffect::lateUpdate()
{
}

void UIEffect::render()
{
}
