#include "pch.h"
#include "PlayerWallSlideState.h"
#include "Components.h"
#include "PlayerFSM.h"

PlayerWallSlideState::PlayerWallSlideState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerWallSlideState::~PlayerWallSlideState()
{
}

void PlayerWallSlideState::InputUpdate()
{
}

void PlayerWallSlideState::Update()
{
}

void PlayerWallSlideState::Enter()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();

	animator->Play(L"WallSlide", false);
}

void PlayerWallSlideState::Exit()
{
}
