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
		memory::safe::DeleteVec(mGameObjects);
	}

	void Layer::initialize()
	{
		//Test Rendering Code

		for (size_t i = 0; i < 1000; i++)
		{
			GameObject* testOBJ = new GameObject;
			testOBJ->GetComponent<Transform>()->SetPosition(-1.0f + i * 0.02f, -0.5f + i * 0.02f, 0.0f);
			mGameObjects.push_back(testOBJ);
		}
		

		/*testOBJ = new GameObject;
		testOBJ->GetComponent<Transform>()->SetPosition(-0.5f, 0.0f, 0.0f);
		mGameObjects.push_back(testOBJ);

		testOBJ = new GameObject;
		testOBJ->GetComponent<Transform>()->SetPosition(0.0f, 0.5f, 0.0f);
		mGameObjects.push_back(testOBJ);

		testOBJ = new GameObject;
		testOBJ->GetComponent<Transform>()->SetPosition(0.0f, -0.5f, 0.0f);
		mGameObjects.push_back(testOBJ);*/

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
			gameObject->render();
		}
	}
}
