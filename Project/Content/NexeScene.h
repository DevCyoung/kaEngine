#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

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

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	eNextSceneState mNextSceneState;
};
