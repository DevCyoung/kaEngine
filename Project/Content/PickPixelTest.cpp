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
    DebugRenderer2D* const debugRenderer = renderer->GetDebugRenderer();

    Camera* const main = renderer->GetRegisteredRenderCamera(eCameraPriorityType::Main);
    Vector3 mouseWorldPos = helper::WindowScreenMouseToWorld3D(main);

    XMINT2 gridPos = helper::GridIndex(mouseWorldPos, Vector2(1,1), XMUINT2(1000000, 1000000));

    mouseWorldPos = helper::GridIndexToWorldPosition(gridPos, Vector2(1, 1), XMUINT2(1000000, 1000000));
    debugRenderer->DrawFillRect2D(mouseWorldPos,Vector2(1, 1), 0.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f)); 

    if (gInput->GetKeyDown(eKeyCode::P))
    {
        GetOwner()->GetComponent<Animator2D>()->Play(L"Roll", false);
    }
    
}

void PickPixelTest::lateUpdate()
{
}
