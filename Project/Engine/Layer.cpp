#include "pch.h"
#include "Layer.h"
#include "GameObject.h"

Layer::Layer()
	:mGameObjects()
{
}

Layer::~Layer()
{
	memory::safe::DeleteVec(mGameObjects);
}

void Layer::AddGameObject(GameObject* const obj)
{
	mGameObjects.push_back(obj);
}

void Layer::initialize()
{
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
