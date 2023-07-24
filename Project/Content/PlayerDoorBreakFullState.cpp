#include "pch.h"
#include "PlayerDoorBreakFullState.h"
#include "Components.h"
#include "PlayerFSM.h"

PlayerDoorBreakFullState::PlayerDoorBreakFullState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerDoorBreakFullState::~PlayerDoorBreakFullState()
{
}

void PlayerDoorBreakFullState::InputUpdate()
{
}

void PlayerDoorBreakFullState::Update()
{
}

void PlayerDoorBreakFullState::Enter()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();

	animator->Play(L"DoorBreakFull", false);
}

void PlayerDoorBreakFullState::Exit()
{
}
