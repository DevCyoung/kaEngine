#include "pch.h"
#include "GridPainter.h"
#include "Components.h"

#include <Engine/GameSystem.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>
#include <Engine/Color.h>
#include <Engine/EngineMath.h>


GridPainter::GridPainter()
    : ScriptComponent(eScriptComponentType::GridPainter)
    , mCellSize(1)
    , mCellCount(XMUINT2(1,1))
    , mbPaint(false)
    , mColor(helper::Color::WHITE)
{
}

GridPainter::~GridPainter()
{
}

void GridPainter::initialize()
{
}

void GridPainter::update()
{   
    if (mbPaint == false)
    {
        return;
    }

    const RenderTargetRenderer* const P_RENDERER = GetOwner()->GetGameSystem()->GetRenderTargetRenderer();
    const Transform* const P_TRANSFORM = GetOwner()->GetComponent<Transform>();

    const Vector2& CELL_SIZE  = Vector2(static_cast<float>(mCellSize), static_cast<float>(mCellSize));    
    const Vector3 POS = P_TRANSFORM->GetPosition();

    DebugRenderer2D* const debugRenderer = P_RENDERER->GetDebugRenderer();

    debugRenderer->DrawGrid2D(POS, CELL_SIZE, mCellCount, 0.f, mColor);    
}

void GridPainter::lateUpdate()
{
}
