#include "Scene.h"
#include "GameObject.h"

namespace engine
{
	Scene::Scene()
		: mGameObjects()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::initialize()
	{
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

	void Scene::render()
	{
		for (GameObject* const gameObject : mGameObjects)
		{
			gameObject->render();
		}
	}
}