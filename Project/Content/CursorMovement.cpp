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
	//if (false == gInput->IsWindowMouseHoverd())
	//{
	//	return;
	//}

	RenderTargetRenderer* const renderTargetRenderer = gEngine->GetRenderTargetRenderer();
	Transform* const transform = GetComponent<Transform>();

	const Camera* const P_UI_CAMERA = renderTargetRenderer->GetRegisteredRenderCamera(Camera::eCameraPriorityType::UI);
	const Vector3 UI_POS = helper::WindowScreenMouseToWorld3D(P_UI_CAMERA);

	transform->SetPosition(UI_POS);

	const Camera* const P_MAIN_CAMERA = renderTargetRenderer->GetRegisteredRenderCamera(Camera::eCameraPriorityType::Main);
	const Vector3 MOUSE_WORLD_3D_POS = helper::WindowScreenMouseToWorld3D(P_MAIN_CAMERA);

	if (gInput->GetKeyDown(eKeyCode::LBTN))
	{
		mPrevClickPos = MOUSE_WORLD_3D_POS;
	}

	DebugRenderer2D * const debugRenderer2D = renderTargetRenderer->GetDebugRenderer();

	const Vector4& fillColor = Vector4(helper::LerpCosBtwZeroAndOne(gGlobalTime),
		helper::LerpSinBtwZeroAndOne(gGlobalTime), 
		helper::LerpSinBtwZeroAndOne(gGlobalTime),
		helper::LerpCosBtwZeroAndOne(gGlobalTime) * 100.f);

	if (gInput->GetKey(eKeyCode::LBTN))
	{
		debugRenderer2D->DrawRect2D2(mPrevClickPos, MOUSE_WORLD_3D_POS, 0.f, fillColor);
	}

	if (gInput->GetKeyUp(eKeyCode::LBTN))
	{
		debugRenderer2D->DrawRect2D2(mPrevClickPos, MOUSE_WORLD_3D_POS, 0.f, fillColor);
	}

	static float size = 32;

	if (gInput->GetKeyDown(eKeyCode::NUM3))
	{
		size += 16;

		if (size > 64)
		{
			size = 32;
		}
	}

	debugRenderer2D->DrawGrid2D(Vector3(0.f, 0.f, 1.f), Vector2(64, 64), Vector2(1000, 1000), 0.f, fillColor);

}

void CursorMovement::lateUpdate()
{
}
