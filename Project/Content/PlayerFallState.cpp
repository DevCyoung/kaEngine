#include "pch.h"
#include "PlayerFallState.h"
#include "Components.h"
#include "PlayerFSM.h"

PlayerFallState::PlayerFallState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerFallState::~PlayerFallState()
{
}

void PlayerFallState::InputUpdate()
{
}

void PlayerFallState::Update()
{
}

void PlayerFallState::Enter()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();

	animator->Play(L"Fall", true);
}

void PlayerFallState::Exit()
{
}
