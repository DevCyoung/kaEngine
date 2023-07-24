#include "pch.h"
#include "PlayerState.h"
#include "PlayerFSM.h"

PlayerState::PlayerState(GameObject* const gameObject, PlayerFSM* const owner)
	: mGameObject(gameObject)
	, mOwner(owner)
{
}

void PlayerState::InputUpdate()
{
}

void PlayerState::Update()
{
}
