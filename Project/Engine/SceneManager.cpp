#include "pch.h"
#include "SceneManager.h"

namespace engine
{	
	SceneManager::SceneManager()
		: mCurrentScene(nullptr)
	{		
	}

	SceneManager::~SceneManager()
	{
		delete mCurrentScene;
		mCurrentScene = nullptr;
	}

	void SceneManager::initialize()
	{
		assert(!sInstance);
		sInstance = new SceneManager();

		sInstance->mCurrentScene = new Scene();	//DummyScene
		sInstance->mCurrentScene->initialize();		
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