#include "pch.h"
#include "DoorController.h"
#include "Components.h"
#include "GameManager.h"
#include <Engine/EngineMath.h>

#include "FolowPlayer.h"

DoorController::DoorController()
    : ScriptComponent(eScriptComponentType::DoorController)
	, mbOpen(false)
{
}

DoorController::~DoorController()
{
}

void DoorController::Open(GameObject* const opener)
{
	if (mbOpen)
	{
		return;
	}

	mbOpen = true;

	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();
	animator->Play(L"Open", false);

	if (helper::math::GetDirection2D(GetOwner(), opener).x > 0.f)
	{
		animator->SetFlipX(true);
	}

	Camera* const camera = GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetRegisteredRenderCamera(eCameraPriorityType::Main);
	camera->GetOwner()->GetComponent<FolowPlayer>()->ShakeCamera();
}

void DoorController::initialize()
{
	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();
	//animator->SetFlipX(true);

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"Open");
		std::function<void()> func = [this]() {
			gSoundManager->Play(eResAudioClip::doorOpen, 1.f);
		};		

		animation->SetFrameStartEvent(0, func);
	}

	//GetOwner()->GetComponent<Transform>()->SetFlipx(true);	
}

void DoorController::update()
{
	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();

	if (gInput->GetKeyDown(eKeyCode::U))
	{
		animator->SetFlipX(true);
	}

	if (gInput->GetKeyDown(eKeyCode::I))
	{
		animator->SetFlipX(false);
	}
}

void DoorController::lateUpdate()
{
}

void DoorController::onCollisionEnter(Collider2D* other)
{
	if (other->GetOwner()->GetLayer() == eLayerType::PlayerAttack)
	{
		Open(other->GetOwner());
	}
}
