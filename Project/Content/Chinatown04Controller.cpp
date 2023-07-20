#include "pch.h"
#include "Chinatown04Controller.h"
#include "Components.h"
#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>

Chinatown04Controller::Chinatown04Controller()
    : ScriptComponent(eScriptComponentType::Chinatown04Controller)
{
}

Chinatown04Controller::~Chinatown04Controller()
{
}

void Chinatown04Controller::initialize()
{
}

void Chinatown04Controller::update()
{
    //DebugRenderer2D* const debugRenderer = GetOwner()->GetRenderTargetRenderer()->GetDebugRenderer();
    //
    //debugRenderer->DrawGrid2D(Vector3::Zero, Vector2(32.f, 32.f), 
    //    XMUINT2(100, 100), 0.f, Vector4(1.f, 1.f, 1.f, 1.f));

}

void Chinatown04Controller::lateUpdate()
{
}

