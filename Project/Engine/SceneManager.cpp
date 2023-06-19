#include "pch.h"
#include "Scene.h"
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

		//FIXME: DummyScene
		sInstance->mCurrentScene = new Scene();
		sInstance->mCurrentScene->initialize();		
	}

	void SceneManager::LoadScene(Scene* const scene)
	{		
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
