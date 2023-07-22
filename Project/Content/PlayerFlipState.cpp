#include "pch.h"
#include "PlayerFlipState.h"
#include "Components.h"
#include "PlayerFSM.h"

PlayerFlipState::PlayerFlipState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerFlipState::~PlayerFlipState()
{
}

void PlayerFlipState::InputUpdate()
{
}

void PlayerFlipState::Update()
{
}

void PlayerFlipState::Enter()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();

	animator->Play(L"Flip", false);
}

void PlayerFlipState::Exit()
{
}
