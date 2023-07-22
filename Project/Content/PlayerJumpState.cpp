#include "pch.h"
#include "PlayerJumpState.h"
#include "Components.h"
#include "PlayerFSM.h"


PlayerJumpState::PlayerJumpState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::InputUpdate()
{
}

void PlayerJumpState::Update()
{
}

void PlayerJumpState::Enter()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();

	animator->Play(L"Jump", true);
}

void PlayerJumpState::Exit()
{
}
