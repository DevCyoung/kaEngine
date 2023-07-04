#include "pch.h"
#include "CameraInputMoveMent.h"
#include "Components.h"
#include <Engine/InputManager.h>
#include <Engine/TimeManager.h>
#include <Engine/MessageManager.h>

CameraInputMoveMent::CameraInputMoveMent()
	: ScriptComponent(eScriptComponentType::CameraInputMoveMent)
{
}

CameraInputMoveMent::~CameraInputMoveMent()
{
}

void CameraInputMoveMent::initialize()
{
}

void CameraInputMoveMent::update()
{
	Camera* const camera = GetComponent<Camera>();

	if (gInput->GetKeyDown(eKeyCode::F1))
	{
		camera->SetProjectiontType(Camera::eProjectionType::Orthographic);
	}
	else if (gInput->GetKeyDown(eKeyCode::F2))
	{
		camera->SetProjectiontType(Camera::eProjectionType::Perspective);
	}	

	constexpr float cameraSpeed = 600.f;

	float fSpeed = cameraSpeed;

	if (gInput->GetKey(eKeyCode::LSHIFT))
	{
		fSpeed *= 5.f;
	}

	Transform* const transform = GetComponent<Transform>();
	if (camera->GetProjectiontType() == Camera::eProjectionType::Orthographic)
	{
		Vector3 pos = transform->GetPosition();
		Vector3 dir = Vector3::Zero;

		if (gInput->GetKey(eKeyCode::W))
		{
			dir.y += 1.f;
		}
		if (gInput->GetKey(eKeyCode::S))
		{
			dir.y += -1.f;
		}
		if (gInput->GetKey(eKeyCode::A))
		{
			dir.x -= 1.f;
		}
		if (gInput->GetKey(eKeyCode::D))
		{
			dir.x += 1.f;
		}

		dir.Normalize();
		dir *= fSpeed * gDeltaTime;
		pos += dir;
		transform->SetPosition(pos);		

		float cameraSize = camera->GetSize();

		if (gInput->GetKey(eKeyCode::NUM1))
		{
			cameraSize += gDeltaTime;
		}
		if (gInput->GetKey(eKeyCode::NUM2))
		{
			cameraSize -= gDeltaTime;
		}

		if (cameraSize < 0.1f)
		{
			cameraSize = 0.1f;
		}
		else if (cameraSize >= 5.f)
		{
			cameraSize = 5.f;
		}

		camera->SetCameraSize(cameraSize);

		if (MessageManager::GetInstance()->IsSendMessage())
		{
			wchar_t buffer[256] = { 0, };
			swprintf_s(buffer, 256, L"<Main Camera Position : %.2f, %.2f, %.2f Size : %.2f>", pos.x, pos.y, pos.z, cameraSize);
			MessageManager::GetInstance()->AddMessage(buffer);
		}		
	}
	else
	{
		Vector3 pos = transform->GetPosition();
		Vector3 rot = transform->GetRotation();
		Vector3 forward = transform->GetForward();
		Vector3 right = transform->GetRight();

		if (gInput->GetKey(eKeyCode::W))
		{
			pos += gDeltaTime * forward * fSpeed;
		}

		if (gInput->GetKey(eKeyCode::S))
		{
			pos -= gDeltaTime * forward * fSpeed;
		}

		if (gInput->GetKey(eKeyCode::A))
		{
			pos -= gDeltaTime * right * fSpeed;
		}

		if (gInput->GetKey(eKeyCode::D))
		{
			pos += gDeltaTime * right * fSpeed;
		}

		if (gInput->GetKey(eKeyCode::RBTN))
		{			
			Vector2 mouseDir = gInput->GetMouseDir();

			rot.y += gDeltaTime	* mouseDir.x * 100.f;
			rot.x -= gDeltaTime * mouseDir.y * 100.f;
		}

		transform->SetPosition(pos);
		transform->SetRotation(rot);
	}
}

void CameraInputMoveMent::lateUpdate()
{
}
