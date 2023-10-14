#include "pch.h"
#include "SlashComponent.h"
#include "Components.h"
#include "GameManager.h"
#include <Engine/EngineMath.h>

SlashComponent::SlashComponent()
    : ScriptComponent(eScriptComponentType::SlashComponent)
{
}

SlashComponent::~SlashComponent()
{
}

void SlashComponent::slashSouind()
{
	gSoundManager->Play(eResAudioClip::slash3);
}

void SlashComponent::initialize()
{
	Animator2D* const animator = GetOwner()->GetComponent<Animator2D>();

	{
		Animation2D* animation = animator->FindAnimationOrNull(L"Slash");

		std::function<void()> func = [this]() {

			int randNum = helper::rand::RandInt(1, 10000) % 3;
			if (0 == randNum)
			{
				gSoundManager->Play(eResAudioClip::slash1, 0.7f);
			}
			else if (1 == randNum)
			{
				gSoundManager->Play(eResAudioClip::slash2, 0.7f);
			}
			else
			{
				gSoundManager->Play(eResAudioClip::slash3, 0.7f);
			}

			GetOwner()->GetComponent<RectCollider2D>()->SetOffset(Vector2(30.f, 0.f));

			//Slash->GetComponent<RectCollider2D>()->SetSize(50.f, 30.f);
			//Slash->GetComponent<RectCollider2D>()->SetOffset(Vector2(30.f, 0.f));			
		};


		std::function<void()> func2 = [this]() {
			GetOwner()->GetComponent<RectCollider2D>()->SetOffset(Vector2(-10000000.f, -10000000.f));
		};

		animation->SetFrameStartEvent(0, func);
		animation->SetFrameStartEvent(3, func2);
	}
}

void SlashComponent::update()
{
}

void SlashComponent::lateUpdate()
{
}
