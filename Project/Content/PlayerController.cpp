#include "pch.h"
#include "PlayerController.h"
#include "Components.h"
#include "PlayerFSM.h"


PlayerController::PlayerController()
	: ScriptComponent(eScriptComponentType::PlayerController)
	, mPlayerFSM(nullptr)
	, mSlash(nullptr)
{
}

PlayerController::~PlayerController()
{
	SAFE_DELETE_POINTER(mPlayerFSM);
}

void PlayerController::initialize()
{
	mPlayerFSM->Initialize(mPlayerFSM->mPlayerIdleState);

	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"IdleToRun");
		std::function<void()> func = std::bind(&PlayerController::idleToRun, this);

		animation->SetLastFrameEndEvent(func);
	}

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"RunToIdle");
		std::function<void()> func = std::bind(&PlayerController::runToIdle, this);

		animation->SetLastFrameEndEvent(func);
	}

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"Roll");
		std::function<void()> func = [this]() {
			this->GetOwner()->GetComponent<Animator2D>()->Play(L"Idle", true);
			this->mPlayerFSM->ChangeState(mPlayerFSM->mPlayerIdleState);
		};

		animation->SetLastFrameEndEvent(func);
	}

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"PostCrouch");
		std::function<void()> func = [this]() {
			this->GetOwner()->GetComponent<Animator2D>()->Play(L"Idle", true);
			this->mPlayerFSM->ChangeState(mPlayerFSM->mPlayerIdleState);
		};

		animation->SetLastFrameEndEvent(func);
	}

	
}

void PlayerController::update()
{
	Assert(mPlayerFSM, WCHAR_IS_NULLPTR);

	mPlayerFSM->GlobalUpdate();
	mPlayerFSM->InputUpdate();
	mPlayerFSM->Update();

	//const float MOVE_SPEED = 300.f;
	//
	//Transform* const transform = GetOwner()->GetComponent<Transform>();
	//Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();
	//
	//Vector3 pos = transform->GetPosition();
	//Vector3 dir = Vector3::Zero;
	//
	//if (gInput->GetKey(eKeyCode::LEFT))
	//{
	//	dir.x -= 1.f;
	//}
	//if (gInput->GetKey(eKeyCode::RIGHT))
	//{
	//	dir.x += 1.f;
	//}
	//
	//if (gInput->GetKey(eKeyCode::UP))
	//{
	//	dir.y += 1.f;
	//}
	//if (gInput->GetKey(eKeyCode::DOWN))
	//{
	//	dir.y -= 1.f;
	//}
	//
	//
	//
	//
	//dir.Normalize();
	//pos += dir * gDeltaTime * MOVE_SPEED;
	//
	//if (dir.x > 0)
	//{
	//	transform->SetRotation(0.f, 0, 0.f);
	//}
	//else if (dir.x < 0)
	//{
	//	transform->SetRotation(0.f, 180.f, 0.f);
	//}
	//
	//
	//if (gInput->GetKeyDown(eKeyCode::LEFT) ||
	//	gInput->GetKeyDown(eKeyCode::RIGHT) ||
	//	gInput->GetKeyDown(eKeyCode::UP) ||
	//	gInput->GetKeyDown(eKeyCode::DOWN))
	//{
	//
	//	if (dir.Length() > 0.1f)
	//	{
	//		animator->Play(L"Run", true);
	//	}
	//	else
	//	{
	//		animator->Play(L"Idle", true);
	//	}
	//}
	//
	//
	//
	//if (gInput->GetKeyDown(eKeyCode::LBTN))
	//{
	//	animator->Play(L"Attack", false);
	//}
	//
	//if (gInput->GetKeyDown(eKeyCode::P))
	//{
	//	animator->Play(L"Roll", false);
	//}
	//
	//
	//transform->SetPosition(pos);
}

void PlayerController::lateUpdate()
{	
}

void PlayerController::idleToRun()
{
	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();

	animator->Play(L"Run", true);
}

void PlayerController::runToIdle()
{
	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();

	animator->Play(L"Idle", true);
}
