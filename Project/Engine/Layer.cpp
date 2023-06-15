#include "pch.h"
#include "Layer.h"
#include "GameObject.h"

namespace engine
{
	Layer::Layer()
		:mGameObjects()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* const gameObject : mGameObjects)
		{
			delete gameObject;
		}
	}

	void Layer::initialize()
	{
		mGameObjects.push_back(new GameObject);

		for (GameObject* const gameObject : mGameObjects)
		{
			gameObject->initialize();
		}
	}
	void Layer::update()
	{
		for (GameObject* const gameObject : mGameObjects)
		{
			gameObject->update();
		}
	}
	void Layer::lateUpdate()
	{
		for (GameObject* const gameObject : mGameObjects)
		{
			gameObject->lateUpdate();
		}
	}
	void Layer::render()
	{
		for (GameObject* const gameObject : mGameObjects)
		{
			gameObject->render(/*mGraphicDevice*/);
		}
	}
}
