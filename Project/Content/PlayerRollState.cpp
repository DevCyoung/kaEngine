#include "pch.h"
#include "PlayerRollState.h"
#include "PlayerFSM.h"
#include "Components.h"

PlayerRollState::PlayerRollState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerRollState::~PlayerRollState()
{
}

void PlayerRollState::InputUpdate()
{
}

void PlayerRollState::Update()
{	
}

void PlayerRollState::Enter()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();
	animator->Play(L"Roll", false);
}

void PlayerRollState::Exit()
{
}
