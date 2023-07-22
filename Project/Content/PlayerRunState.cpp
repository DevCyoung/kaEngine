#include "pch.h"
#include "PlayerRunState.h"
#include "PlayerFSM.h"
#include "Components.h"

PlayerRunState::PlayerRunState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerRunState::~PlayerRunState()
{
}

void PlayerRunState::InputUpdate()
{

}

void PlayerRunState::Update()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();

	if (gInput->GetKey(eKeyCode::LEFT) == false &&
		gInput->GetKey(eKeyCode::RIGHT) == false)
	{
		animator->Play(L"RunToIdle", false);
		mOwner->ChangeState(mOwner->mPlayerIdleState);
		return;
	}

	Vector3 dir = Vector3::Zero;

	if (gInput->GetKey(eKeyCode::LEFT))
	{
		dir.x -= 1.f;
	}
	if (gInput->GetKey(eKeyCode::RIGHT))
	{
		dir.x += 1.f;
	}

	if (dir.Length() < 0.1f)
	{
		animator->Play(L"RunToIdle", false);
		mOwner->ChangeState(mOwner->mPlayerIdleState);
		return;
	}

	if (gInput->GetKeyDown(eKeyCode::DOWN))
	{
		mOwner->ChangeState(mOwner->mPlayerRollState);
		return;
	}

	Transform* const transform = mGameObject->GetComponent<Transform>();

	float speed = 500.f;

	Vector3 pos = dir * speed * gDeltaTime + transform->GetPosition();

	transform->SetPosition(pos);

	if (dir.x < 0)
	{
		transform->SetRotation(0.f, 180.f, 0.f);
	}
	else if (dir.x > 0)
	{
		transform->SetRotation(0.f, 0.f, 0.f);
	}

}

void PlayerRunState::Enter()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();
	animator->Play(L"IdleToRun", false);
}

void PlayerRunState::Exit()
{
}
