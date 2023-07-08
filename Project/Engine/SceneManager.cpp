#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager()
	: mCurrentScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	DELETE_POINTER(mCurrentScene);
}

void SceneManager::LoadScene(Scene* const scene)
{
	Assert(scene, WCHAR_IS_NULLPTR);
	DELETE_ARRAY(sInstance->mCurrentScene);

	mCurrentScene = scene;
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

void SceneManager::eventUpdate()
{
	mCurrentScene->eventUpdate();
}
