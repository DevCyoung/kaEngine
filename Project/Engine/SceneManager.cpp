#include "pch.h"
#include "Scene.h"
#include "SceneManager.h"

namespace engine
{
	SceneManager::SceneManager()
		: mCurrentScene(nullptr)

	{
		//FIXME: DummyScene		
		mCurrentScene = new Scene();
		mCurrentScene->initialize();
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
	}

	void SceneManager::update()
	{
		mCurrentScene->update();
	}
	void SceneManager::lateUpdate()
	{
		mCurrentScene->lateUpdate();
	}
	void SceneManager::render()
	{
		mCurrentScene->render();
	}
}
