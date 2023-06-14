#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

#include "Shader.h"

namespace engine
{
	Scene::Scene()
		: mGameObjects()
	{
	}

	Scene::~Scene()
	{
		for (GameObject* const gameObject : mGameObjects)
		{
			delete gameObject;
		}
	}

	void Scene::initialize()
	{
		mGameObjects.push_back(new GameObject);

		for (GameObject* const gameObject : mGameObjects)
		{
			gameObject->initialize();			
		}		
	}

	void Scene::update()
	{
		for (GameObject* const gameObject : mGameObjects)
		{
			gameObject->update();
		}
	}

	void Scene::lateUpdate()
	{
		for (GameObject* const gameObject : mGameObjects)
		{
			gameObject->lateUpdate();
		}
	}

	void Scene::render(/*mGraphicDevice*/)
	{
		for (GameObject* const gameObject : mGameObjects)
		{
			gameObject->render(/*mGraphicDevice*/);			
		}
	}

}