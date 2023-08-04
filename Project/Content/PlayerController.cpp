#include "pch.h"
#include "PlayerController.h"
#include "Components.h"
#include "PlayerFSM.h"
#include "Rect2DInterpolation.h"

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

		{
			std::function<void()> func = std::bind(&PlayerController::idleToRun, this);
			animation->SetLastFrameEndEvent(func);
		}
	}

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"RunToIdle");


		{
			std::function<void()> func = std::bind(&PlayerController::runToIdleVeloZero, this);
			animation->SetFrameEndEvent(3, func);
		}

		{
			std::function<void()> func = std::bind(&PlayerController::runToIdle, this);
			animation->SetLastFrameEndEvent(func);
		}			

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

	{
		std::function<void()> func = [this]() {

			//Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();

			if (GetOwner()->GetComponent<Rect2DInterpolation>()->IsCollisionWallFloor() || GetOwner()->GetComponent<Rect2DInterpolation>()->IsCollisionWallSlop())
			{
				mPlayerFSM->mPlayerGlobalState->RunToIdle();
			}
			else
			{
				//animator->Play(L"Fall", true);
				mPlayerFSM->ChangeState(mPlayerFSM->mPlayerFallState);
			}


		};

		Animation2D* animation = animator->FindAnimationOrNull(L"Attack");

		animation->SetLastFrameEndEvent(func);
	}


}

void PlayerController::update()
{
	Assert(mPlayerFSM, WCHAR_IS_NULLPTR);

	mPlayerFSM->GlobalUpdate();

	mPlayerFSM->InputUpdate();

	mPlayerFSM->Update();
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
	//Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();

	animator->Play(L"Idle", true);
	//rigidbody->SetVelocity(Vector2(0.f, 0.f));
}

void PlayerController::runToIdleVeloZero()
{
	Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();
	rigidbody->SetVelocity(Vector2::Zero);
}

void PlayerController::toFall()
{
	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();

	animator->Play(L"Fall", true);
}
