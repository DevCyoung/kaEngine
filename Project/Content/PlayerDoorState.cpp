#include "pch.h"
#include "PlayerDoorState.h"
#include "Components.h"
#include "PlayerFSM.h"

PlayerDoorState::PlayerDoorState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerDoorState::~PlayerDoorState()
{
}

void PlayerDoorState::InputUpdate()
{
}

void PlayerDoorState::Update()
{
}

void PlayerDoorState::Enter()
{
}

void PlayerDoorState::Exit()
{
}
