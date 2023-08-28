#include "pch.h"
#include "PickPixelTest.h"
#include "Components.h"

#include <Engine/GameSystem.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>
#include <Engine/EngineMath.h>
#include <Engine/Animator2D.h>
PickPixelTest::PickPixelTest()
    : ScriptComponent(eScriptComponentType::PickPixelTest)
{
}

PickPixelTest::~PickPixelTest()
{
}

void PickPixelTest::initialize()
{
}

void PickPixelTest::update()
{
    RenderTargetRenderer* const renderer = GetOwner()->GetGameSystem()->GetRenderTargetRenderer();
    DebugRenderer2D* const debugRenderer = renderer->GetDebugRenderer2D();

    Camera* const main = renderer->GetRegisteredRenderCamera(eCameraPriorityType::Main);
    Vector3 mouseWorldPos = helper::WindowScreenMouseToWorld3D(main);

    XMINT2 gridPos = helper::GridIndex(mouseWorldPos, Vector2(32,32), XMUINT2(1000000, 1000000));

    mouseWorldPos = helper::GridIndexToWorldPosition(gridPos, Vector2(32, 32), XMUINT2(1000000, 1000000));
    debugRenderer->DrawFillRect2D(mouseWorldPos,Vector2(32, 32), 0.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f));     
}

void PickPixelTest::lateUpdate()
{
}
