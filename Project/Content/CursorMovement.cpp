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
#include "GameObjectBuilder.h"
#include "BulletMovement.h"
#include <Engine/SceneManager.h>
#include <Engine/EngineMath.h>
#include <Engine/GameSystem.h>

using namespace helper;
using namespace helper::math;

CursorMovement::CursorMovement()
	: ScriptComponent(eScriptComponentType::CursorMovement)
	, mDelay(0.f)
{
}

CursorMovement::~CursorMovement()
{
}

void CursorMovement::onCollisionEnter(Collider2D* other)
{
	(void)other;
}

void CursorMovement::initialize()
{
}

void CursorMovement::update()
{
	//const Vector4& FILL_COLOR = Vector4(LerpCosBtwZeroAndOne(gGlobalTime),
	//	LerpSinBtwZeroAndOne(gGlobalTime),
	//	LerpSinBtwZeroAndOne(gGlobalTime),
	//	LerpCosBtwZeroAndOne(gGlobalTime) * 100.f);
	//
	RenderTargetRenderer* const renderTargetRenderer = GetOwner()->GetGameSystem()->GetRenderTargetRenderer();
	//DebugRenderer2D* const debugRenderer2D = renderTargetRenderer->GetDebugRenderer();
	
	Transform* const transform = GetOwner()->GetComponent<Transform>();
	//
	//const Camera* const P_UI_CAMERA =
	//	renderTargetRenderer->GetRegisteredRenderCamera(eCameraPriorityType::UI);
	//
	const Camera* const P_MAIN_CAMERA =
		renderTargetRenderer->GetRegisteredRenderCamera(eCameraPriorityType::Main);

	//const Vector3 UI_MOUSE_POS = WindowScreenMouseToWorld3D(P_UI_CAMERA);
	const Vector3& MOUSE_WORLD_3D_POS = WindowScreenMouseToWorld3D(P_MAIN_CAMERA);
	
	Vector3 mousePos = MOUSE_WORLD_3D_POS;
	mousePos.z = 0.f;
	
	transform->SetPosition(mousePos);


	

	//static float  delay = 0.f;

	mDelay += gDeltaTime;

	if (mDelay > 0.0025f)
	{
		GameObject* const bullet = GameObjectBuilder::BuildDefault2DGameObject(L"UIRightItem");
		bullet->AddComponent<BulletMovement>();
		bullet->AddComponent <CircleCollider2D> ();
		
		Vector3 dir = Vector3(cosf(gGlobalTime * 10.f), sinf(gGlobalTime * 10.f), 0.f);		


		bullet->GetComponent<Transform>()->SetPosition(MOUSE_WORLD_3D_POS + dir * 100.f);
		bullet->GetComponent<BulletMovement>()->mDir = dir;
		bullet->GetComponent<CircleCollider2D>()->SetRadius(20.f);

		gCurrentScene->RegisterEventAddGameObject(bullet, eLayerType::Bullet);
		
		mDelay = 0.f;
	}	


	if (gInput->GetKeyDown(eKeyCode::P))
	{
		renderTargetRenderer->TurnOffDebugRenderer();
	}
	if (gInput->GetKeyDown(eKeyCode::O))
	{
		renderTargetRenderer->TurnOnDebugRenderer();
	}


	//const Vector3 GRID_WORLD_POS = Vector3(0.f, 0.f, 1.f);
	//const XMUINT2 TILE_COUNT_XY = XMUINT2(500, 500);
	//
	//static float size = 32;
	//
	//const Vector2 CELL_SIZE_XY = Vector2(size, size);
	//
	//transform->SetPosition(UI_MOUSE_POS);
	//
	//debugRenderer2D->DrawGrid2D(GRID_WORLD_POS,
	//	CELL_SIZE_XY, TILE_COUNT_XY, 0.f, FILL_COLOR);
	//
	//const XMINT2 INDEX_XY = GridIndex(MOUSE_WORLD_3D_POS,
	//	CELL_SIZE_XY, TILE_COUNT_XY);
	//const Vector3& RECT_POS = GridIndexToWorldPosition(INDEX_XY, CELL_SIZE_XY,
	//	TILE_COUNT_XY);
	//
	//if (gInput->GetKeyDown(eKeyCode::NUM3))
	//{
	//	size += 16;
	//
	//	if (size > 128)
	//	{
	//		size = 16;
	//	}
	//}

	//if (gInput->GetKeyDown(eKeyCode::O))
	//{
	//	renderTargetRenderer->TurnOnCamera(eCameraPriorityType::UI);
	//}
	//if (gInput->GetKeyDown(eKeyCode::P))
	//{
	//	renderTargetRenderer->TurnOffCamera(eCameraPriorityType::UI);
	//}
	//
	//if (gInput->GetKeyDown(eKeyCode::K))
	//{
	//	renderTargetRenderer->TurnOnCamera(eCameraPriorityType::Main);
	//}
	//if (gInput->GetKeyDown(eKeyCode::L))
	//{
	//	renderTargetRenderer->TurnOffCamera(eCameraPriorityType::Main);
	//}
	//
	//if (gInput->GetKeyDown(eKeyCode::N))
	//{
	//	renderTargetRenderer->TurnOnDebugRenderer();
	//}
	//if (gInput->GetKeyDown(eKeyCode::M))
	//{
	//	renderTargetRenderer->TurnOffDebugRenderer();
	//}
	//
	//debugRenderer2D->DrawCircle2D(MOUSE_WORLD_3D_POS,
	//	size * 5.5f, 0.f, Vector4(LerpSinBtwZeroAndOne(gGlobalTime), 0.f, 1.f, 1.f));
	//
	//debugRenderer2D->DrawFillCircle2D(MOUSE_WORLD_3D_POS,
	//	size * 0.5f * 5.f * LerpSinBtwZeroAndOne(gGlobalTime), 0.f, 
	//	Vector4(1.f, LerpSinBtwZeroAndOne(gGlobalTime), 1.f, 1.f));
	//
	//debugRenderer2D->DrawRect2D(MOUSE_WORLD_3D_POS, Vector2(size * 15.f, size * 15.f), 
	//	Vector3::Zero, 0.f, Vector4(1.f, 0.f, LerpSinBtwZeroAndOne(gGlobalTime), 1.f));
	//
	//debugRenderer2D->DrawFillRect2D(MOUSE_WORLD_3D_POS + Vector3(-100.f, +100.f, 0.f),
	//	Vector2(50.f, 50.f), 0.f, Vector4(0.f, 1.f, 1.f, 0.3f));
	//debugRenderer2D->DrawFillRect2D(MOUSE_WORLD_3D_POS + Vector3(+100.f, +100.f, 0.f),
	//	Vector2(50.f, 50.f), 0.f, Vector4(0.f, 1.f, 1.f, 0.3f));
	//debugRenderer2D->DrawFillRect2D(MOUSE_WORLD_3D_POS + Vector3(+100.f, -100.f, 0.f),
	//	Vector2(50.f, 50.f), 0.f, Vector4(0.f, 1.f, 1.f, 0.3f));
	//debugRenderer2D->DrawFillRect2D(MOUSE_WORLD_3D_POS + Vector3(-100.f, -100.f, 0.f),
	//	Vector2(50.f, 50.f), 0.f, Vector4(0.f, 1.f, 1.f, 0.3f));
	//
	//{
	//	const XMINT2 INDEX_XY2 = GridIndex(MOUSE_WORLD_3D_POS + Vector3(-100.f, +100.f, 0.f),
	//		CELL_SIZE_XY, TILE_COUNT_XY);
	//	const Vector3& RECT_POS2 = GridIndexToWorldPosition(INDEX_XY2, CELL_SIZE_XY,
	//		TILE_COUNT_XY);
	//
	//	debugRenderer2D->DrawFillRect2D(RECT_POS2,
	//		CELL_SIZE_XY, 0.f, Vector4(0.f, 1.f, 1.f, 0.4f));
	//}
	//
	//{
	//	const XMINT2 INDEX_XY2 = GridIndex(MOUSE_WORLD_3D_POS + Vector3(+100.f, +100.f, 0.f),
	//		CELL_SIZE_XY, TILE_COUNT_XY);
	//	const Vector3& RECT_POS2 = GridIndexToWorldPosition(INDEX_XY2, CELL_SIZE_XY,
	//		TILE_COUNT_XY);
	//
	//	debugRenderer2D->DrawFillRect2D(RECT_POS2,
	//		CELL_SIZE_XY, 0.f, Vector4(0.f, 1.f, 1.f, 0.4f));
	//}
	//
	//{
	//	const XMINT2 INDEX_XY2 = GridIndex(MOUSE_WORLD_3D_POS + Vector3(+100.f, -100.f, 0.f),
	//		CELL_SIZE_XY, TILE_COUNT_XY);
	//	const Vector3& RECT_POS2 = GridIndexToWorldPosition(INDEX_XY2, CELL_SIZE_XY,
	//		TILE_COUNT_XY);
	//
	//	debugRenderer2D->DrawFillRect2D(RECT_POS2,
	//		CELL_SIZE_XY, 0.f, Vector4(0.f, 1.f, 1.f, 0.4f));
	//}
	//
	//{
	//	const XMINT2 INDEX_XY2 = GridIndex(MOUSE_WORLD_3D_POS + Vector3(-100.f, -100.f, 0.f),
	//		CELL_SIZE_XY, TILE_COUNT_XY);
	//	const Vector3& RECT_POS2 = GridIndexToWorldPosition(INDEX_XY2, CELL_SIZE_XY,
	//		TILE_COUNT_XY);
	//
	//	debugRenderer2D->DrawFillRect2D(RECT_POS2,
	//		CELL_SIZE_XY, 0.f, Vector4(0.f, 1.f, 1.f, 0.4f));
	//}
	//
	//
	//
	//debugRenderer2D->DrawLine2D2(MOUSE_WORLD_3D_POS,
	//	Vector2(1.f, 0.0f), 100.f, 0.f, Vector4(0.f, 0.f, 1.f, 1.f));
	//debugRenderer2D->DrawLine2D2(MOUSE_WORLD_3D_POS,
	//	Vector2(-1.f, 0.0f), 100.f, 0.f, Vector4(0.f, 0.f, 1.f, 1.f));
	//debugRenderer2D->DrawLine2D2(MOUSE_WORLD_3D_POS,
	//	Vector2(0.f, 1.0f), 100.f, 0.f, Vector4(0.f, 0.f, 1.f, 1.f));
	//debugRenderer2D->DrawLine2D2(MOUSE_WORLD_3D_POS,
	//	Vector2(0.f, -1.0f), 100.f, 0.f, Vector4(0.f, 0.f, 1.f, 1.f));
	//
	//debugRenderer2D->DrawLine2D(MOUSE_WORLD_3D_POS + Vector3(-100.f, +100.f, 0.f),
	//	MOUSE_WORLD_3D_POS, 0.f, Vector4(1.f, 0.f, 1.f, 1.f));
	//debugRenderer2D->DrawLine2D(MOUSE_WORLD_3D_POS + Vector3(+100.f, +100.f, 0.f),
	//	MOUSE_WORLD_3D_POS, 0.f, Vector4(1.f, 0.f, 1.f, 1.f));
	//debugRenderer2D->DrawLine2D(MOUSE_WORLD_3D_POS + Vector3(+100.f, -100.f, 0.f),
	//	MOUSE_WORLD_3D_POS, 0.f, Vector4(1.f, 0.f, 1.f, 1.f));
	//debugRenderer2D->DrawLine2D(MOUSE_WORLD_3D_POS + Vector3(-100.f, -100.f, 0.f),
	//	MOUSE_WORLD_3D_POS, 0.f, Vector4(1.f, 0.f, 1.f, 1.f));
	//
	//
	//
	//if (gInput->GetKeyDown(eKeyCode::RBTN))
	//{
	//	mPrevClickPos = MOUSE_WORLD_3D_POS;
	//}
	//
	//if (gInput->GetKey(eKeyCode::RBTN))
	//{
	//	debugRenderer2D->DrawLine2D(mPrevClickPos, MOUSE_WORLD_3D_POS, 0.f, Vector4(1.f, 0.f, 0.f, 1.f));
	//}
	//
	//if (IsInGrid(INDEX_XY, TILE_COUNT_XY))
	//{
	//	if (gInput->GetKey(eKeyCode::LBTN))
	//	{
	//		debugRenderer2D->DrawFillRect2D(RECT_POS, CELL_SIZE_XY, 1.5f, Vector4(1.f, 0.f, 1.f, 1.f));
	//	}
	//	else
	//	{
	//		debugRenderer2D->DrawFillRect2D(RECT_POS, CELL_SIZE_XY, 0.f, Vector4(0.f, 1.f, 0.f, 0.5f));
	//	}
	//
	//	if (gInput->GetKey(eKeyCode::RBTN))
	//	{
	//		const XMINT2 PREV_INDEX_XY = helper::GridIndex(mPrevClickPos, CELL_SIZE_XY, TILE_COUNT_XY);
	//		XMINT2 min = {};
	//		XMINT2 max = {};
	//
	//		helper::math::INT2MinAndMax(INDEX_XY, PREV_INDEX_XY, &min, &max);
	//		Vector3 leftUpPos = helper::GridIndexToWorldPosition(min, CELL_SIZE_XY, TILE_COUNT_XY);
	//		Vector3 rightDownPos = helper::GridIndexToWorldPosition(max, CELL_SIZE_XY, TILE_COUNT_XY);
	//
	//		leftUpPos.x -= CELL_SIZE_XY.x * 0.5f;
	//		leftUpPos.y += CELL_SIZE_XY.y * 0.5f;
	//
	//		rightDownPos.x += CELL_SIZE_XY.x * 0.5f;
	//		rightDownPos.y -= CELL_SIZE_XY.y * 0.5f;
	//
	//		debugRenderer2D->DrawFillRect2D2(leftUpPos, rightDownPos, 0.f, Vector4(1.f, 0.f, 0.f, 0.5f));
	//	}
	//}
	//
	//if (MessageManager::GetInstance()->IsAddTitleMessage())
	//{
	//	wchar_t buffer[256];
	//	swprintf_s(buffer, 256, L"<tile X : %d, Y : %d>", INDEX_XY.x, INDEX_XY.y);
	//	MessageManager::GetInstance()->AddTitleMessage(buffer);
	//}
}

void CursorMovement::lateUpdate()
{
}
