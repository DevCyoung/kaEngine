#include "pch.h"
#include "CursorMovement.h"
#include "Components.h"
#include <Engine/InputManager.h>
#include <Engine/TimeManager.h>
#include <Engine/MessageManager.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>
#include <Engine/EngineMath.h>
#include <Engine/Engine.h>

using namespace helper;
using namespace helper::math;

CursorMovement::CursorMovement()
	: ScriptComponent(eScriptComponentType::CursorMovement)
{
}

CursorMovement::~CursorMovement()
{
}

void CursorMovement::initialize()
{
}

void CursorMovement::update()
{
	RenderTargetRenderer* const renderTargetRenderer = gEngine->GetRenderTargetRenderer();
	const Camera* const P_UI_CAMERA =
		renderTargetRenderer->GetRegisteredRenderCamera(eCameraPriorityType::UI);
	const Vector3 UI_POS = WindowScreenMouseToWorld3D(P_UI_CAMERA);
	Transform* const transform = GetComponent<Transform>();

	transform->SetPosition(UI_POS);

	const Camera* const P_MAIN_CAMERA =
		renderTargetRenderer->GetRegisteredRenderCamera(eCameraPriorityType::Main);
	const Vector3 MOUSE_WORLD_3D_POS = WindowScreenMouseToWorld3D(P_MAIN_CAMERA);

	DebugRenderer2D* const debugRenderer2D = renderTargetRenderer->GetDebugRenderer();
	const Vector4& fillColor = Vector4(LerpCosBtwZeroAndOne(gGlobalTime),
		LerpSinBtwZeroAndOne(gGlobalTime),
		LerpSinBtwZeroAndOne(gGlobalTime),
		LerpCosBtwZeroAndOne(gGlobalTime) * 100.f);

	const Vector3 GRID_WORLD_POS = Vector3(0.f, 0.f, 1.f);
	const tUINT2 TILE_COUNT_XY = tUINT2(50, 50);

	static float size = 16;

	if (gInput->GetKeyDown(eKeyCode::NUM3))
	{
		size += 16;

		if (size > 128)
		{
			size = 16;
		}
	}

	const Vector2 CELL_SIZE_XY = Vector2(size, size);

	debugRenderer2D->DrawGrid2D(GRID_WORLD_POS,
		CELL_SIZE_XY, TILE_COUNT_XY, 0.f, fillColor);

	const tINT2 INDEX_XY = GridIndex(MOUSE_WORLD_3D_POS,
		CELL_SIZE_XY, TILE_COUNT_XY);
	const Vector3& RECT_POS = GridIndexToWorldPosition(INDEX_XY, CELL_SIZE_XY,
		TILE_COUNT_XY);

	if (MessageManager::GetInstance()->IsAddTitleMessage())
	{
		wchar_t buffer[256];
		swprintf_s(buffer, 256, L"<tile X : %d, Y : %d>", INDEX_XY.x, INDEX_XY.y);
		MessageManager::GetInstance()->AddTitleMessage(buffer);
	}

	if (IsInGrid(INDEX_XY, TILE_COUNT_XY) == false)
	{
		return;
	}

	if (gInput->GetKey(eKeyCode::LBTN))
	{
		debugRenderer2D->DrawFillRect2D(RECT_POS, CELL_SIZE_XY, 1.5f, Vector4(1.f, 0.f, 1.f, 1.f));
	}
	else
	{
		debugRenderer2D->DrawFillRect2D(RECT_POS, CELL_SIZE_XY, 0.f, Vector4(0.f, 1.f, 0.f, 0.5f));
	}

	if (gInput->GetKeyDown(eKeyCode::RBTN))
	{
		mPrevClickPos = MOUSE_WORLD_3D_POS;
	}
	
	if (gInput->GetKey(eKeyCode::RBTN))
	{
		const tINT2 PREV_INDEX_XY = helper::GridIndex(mPrevClickPos, CELL_SIZE_XY, TILE_COUNT_XY);
		tINT2 min = {};
		tINT2 max = {};

		helper::math::INT2MinAndMax(INDEX_XY, PREV_INDEX_XY, &min, &max);	
		Vector3 leftUpPos = helper::GridIndexToWorldPosition(min, CELL_SIZE_XY, TILE_COUNT_XY);
		Vector3 rightDownPos = helper::GridIndexToWorldPosition(max, CELL_SIZE_XY, TILE_COUNT_XY);

		leftUpPos.x -= CELL_SIZE_XY.x * 0.5f;
		leftUpPos.y += CELL_SIZE_XY.y * 0.5f;

		rightDownPos.x += CELL_SIZE_XY.x * 0.5f;
		rightDownPos.y -= CELL_SIZE_XY.y * 0.5f;

		debugRenderer2D->DrawFillRect2D2(leftUpPos, rightDownPos, 0.f, Vector4(1.f, 0.f, 0.f, 0.5f));
	
	}
}

void CursorMovement::lateUpdate()
{
}
