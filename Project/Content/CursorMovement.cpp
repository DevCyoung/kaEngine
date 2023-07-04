#include "pch.h"
#include "CursorMovement.h"
#include "Components.h"
#include <Engine/InputManager.h>
#include <Engine/TimeManager.h>
#include <Engine/MessageManager.h>
#include <Engine/RenderTargetRenderer.h>
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
	if (false == gInput->IsWindowMouseHoverd())
	{
		return;
	}

	RenderTargetRenderer* const renderTargetRenderer = gEngine->GetRenderTargetRenderer();
	const Camera* const P_MAIN_CAMERA = renderTargetRenderer->GetRegisteredRenderCamera(Camera::eCameraPriorityType::Main);

	const Vector2 MOUSE_WORLD_2D_POS = helper::WindowScreenMouseToWorld2D(P_MAIN_CAMERA);

	Transform* const transform = GetComponent<Transform>();

	transform->SetPosition(Vector3(MOUSE_WORLD_2D_POS.x, MOUSE_WORLD_2D_POS.y, transform->GetPosition().z));	

	if (gInput->GetKeyDown(eKeyCode::LBTN))
	{
		mPrevClickPos = MOUSE_WORLD_2D_POS;
	}

	if (gInput->GetKey(eKeyCode::LBTN))
	{
		renderTargetRenderer->DrawRect2(mPrevClickPos, MOUSE_WORLD_2D_POS, 0.f);
	}

	if (gInput->GetKeyUp(eKeyCode::LBTN))
	{
		renderTargetRenderer->DrawRect2(mPrevClickPos, MOUSE_WORLD_2D_POS, 3.f);
	}
	
}

void CursorMovement::lateUpdate()
{
}
