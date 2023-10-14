#include "pch.h"
#include "NexeScene.h"
#include "Components.h"
#include "GameManager.h"

NexeScene::NexeScene()
	: ScriptComponent(eScriptComponentType::NexeScene)
	, mNextSceneState(eNextSceneState::None)
{
}

NexeScene::~NexeScene()
{
}

void NexeScene::initialize()
{
}

void NexeScene::update()
{

	SpriteRenderer* spriteRenderer = GetOwner()->GetComponent<SpriteRenderer>();

	float scale = spriteRenderer->GetSprite2DInfo().A;
	float _small = spriteRenderer->GetSprite2DInfo().B;

	switch (mNextSceneState)
	{
	case eNextSceneState::None:
		scale = 1.0f;
		break;
	case eNextSceneState::NextScene:
		scale += gDeltaTime * 3.8f;
		break;
	case eNextSceneState::EnterScene:
		scale -= gDeltaTime * 3.8f;
		break;
	default:
		break;
	}

	if (gInput->GetKeyDown(eKeyCode::J))
	{
		mNextSceneState = eNextSceneState::NextScene;
		gSoundManager->Play(eResAudioClip::TransitionEnd, 0.3f);
		scale = 0.0f;
	}

	if (gInput->GetKeyDown(eKeyCode::K))
	{
		mNextSceneState = eNextSceneState::EnterScene;
		gSoundManager->Play(eResAudioClip::TransitionBegin, 0.3f);
		scale = 1.0f;
	}



	spriteRenderer->SetColorB(_small);
	spriteRenderer->SetColorA(scale);
}

void NexeScene::lateUpdate()
{
}
