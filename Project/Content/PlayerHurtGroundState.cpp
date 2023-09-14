#include "pch.h"
#include "PlayerHurtGroundState.h"
#include "Components.h"
#include "PlayerFSM.h"
#include "Rect2DInterpolation.h"


PlayerHurtGroundState::PlayerHurtGroundState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerHurtGroundState::~PlayerHurtGroundState()
{
}

void PlayerHurtGroundState::InputUpdate()
{
}

void PlayerHurtGroundState::Update()
{
}

void PlayerHurtGroundState::Enter()
{
	mAnimator->Play(L"HurtGround", false);
}

void PlayerHurtGroundState::Exit()
{
}
