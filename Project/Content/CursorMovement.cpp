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
	const Vector2 screenSize = gEngine->GetScreenSize();

	if (false == gInput->IsMouseHoverd(screenSize))
	{
		return;
	}

	const Camera* const mainCamera = gEngine->GetRenderTargetRenderer()->GetRegisteredRenderCamera(Camera::eCameraType::Main);

	const Transform* const cameraTransform = mainCamera->GetComponent<Transform>();

	const Vector2 screenMousePos = gInput->GetMousePos();	
	const Vector3 mainCameraPos = cameraTransform->GetPosition();
	const float mainCameraSize = mainCamera->GetSize();	

	const Vector2 pos = helper::ScreenToWorld2D(screenMousePos,
		screenSize,
		mainCameraPos,
		mainCameraSize);

	//const Vector2 pos = helper::ScreenToWorldScreen(screenMousePos, screenSize);

	Transform* const transform = GetComponent<Transform>();

	transform->SetPosition(Vector3(pos.x, pos.y, transform->GetPosition().z));
}

void CursorMovement::lateUpdate()
{
}
