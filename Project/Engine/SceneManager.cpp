#include "pch.h"
#include "Scene.h"
#include "SceneManager.h"

SceneManager::SceneManager()
	: mCurrentScene(nullptr)

{
}

SceneManager::~SceneManager()
{
	delete mCurrentScene;
	mCurrentScene = nullptr;
}

void SceneManager::LoadScene(Scene* const scene)
{
	Assert(scene, WCHAR_IS_NULLPTR);
	DELETE_ARRAY(sInstance->mCurrentScene);

	sInstance->mCurrentScene = scene;
	scene->initialize();
}

void SceneManager::update()
{
	mCurrentScene->update();
}
void SceneManager::lateUpdate()
{
	mCurrentScene->lateUpdate();
}
