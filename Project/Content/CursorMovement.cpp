#include "pch.h"
#include "CursorMovement.h"
#include "Components.h"
#include <Engine/InputManager.h>
#include <Engine/TimeManager.h>
#include <Engine/MessageManager.h>
#include <Engine/RenderManager.h>
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
	
	Camera* const mainCamera = RenderManager::GetInstance()->GetCamera(Camera::eCameraType::Main);
	
	Transform* const transform = GetComponent<Transform>();
	Transform* const cameraTransform = mainCamera->GetComponent<Transform>();	
	(void)cameraTransform;

	const Vector2 screenMousePos = gInput->GetMousePos();
	const Vector3 mainCameraPos = mainCamera->GetComponent<Transform>()->GetPosition();

	const Vector2 pos = helper::ScreenToWorld2D(screenMousePos,
		screenSize,
		cameraTransform->GetPosition(),
		mainCamera->GetSize());

	//const Vector2 pos = helper::ScreenToWorldScreen(screenMousePos, screenSize);

	transform->SetPosition(Vector3(pos.x, pos.y, transform->GetPosition().z));

}

void CursorMovement::lateUpdate()
{
}

void CursorMovement::render()
{
}
