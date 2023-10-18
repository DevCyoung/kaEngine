#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include "KatanaScene.h"

REGISTER_SCRIPTCOMPONENT_TYPE(NexeScene);

enum class eNextSceneState
{
	None,
	NextScene,
	EnterScene,
};

class NexeScene : public ScriptComponent
{
public:
	NexeScene();
	virtual ~NexeScene();
	NexeScene(const NexeScene&) = delete;
	NexeScene& operator=(const NexeScene&) = delete;

	void FadeIn();
	void FadeOut(eKatanaSceneType nextSceneType);
	void LoadNextScene(eKatanaSceneType sceneType);

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	eNextSceneState mSceneState;
	eKatanaSceneType mNextSceneType;
};
