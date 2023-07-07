#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "MessageManager.h"

Scene::Scene()
	: mLayers()
	, mEventMessages()
	, mGarbages()
{
	mEventMessages.reserve(100);
	mGarbages.reserve(100);
}

Scene::~Scene()
{
}

void Scene::initialize()
{
	for (Layer& layer : mLayers)
	{
		layer.initialize();
	}
}

void Scene::update()
{
	for (Layer& layer : mLayers)
	{
		layer.update();
	}
}

void Scene::lateUpdate()
{
	size_t gameObjectCount = 0;

	for (Layer& layer : mLayers)
	{
		layer.lateUpdate();

		gameObjectCount += layer.mGameObjects.size();

		//if exist garbage, remove it, No rendering
		if (mGarbages.empty() == false)
		{
			std::vector<GameObject*>& gameObjects = layer.mGameObjects;
			gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
				[](const GameObject* const P_GAME_OBJECT) { return P_GAME_OBJECT->mState == GameObject::eState::Destroy; }), gameObjects.end());
		}
	}	

	if (MessageManager::GetInstance()->IsSendMessage())
	{
		wchar_t buff[256] = { 0, };
		swprintf_s(buff, 256, L"<GameObject Count : %zu>", gameObjectCount);
		MessageManager::GetInstance()->AddMessage(buff);
	}
}

void Scene::eventUpdate()
{
	memory::safe::DeleteVec(mGarbages);

	for (auto& message : mEventMessages)
	{
		const eEventOfScene EVENT_TYPE = message.EventOfSceneType;
		Assert(message.EventGameObject, WCHAR_IS_NULLPTR);

		switch (EVENT_TYPE)
		{
		case eEventOfScene::DestroyGameObject:			
			Assert(message.EventGameObject->mState != GameObject::eState::Destroy, WCHAR_IS_INVALID_TYPE);

			message.EventGameObject->mState = GameObject::eState::Destroy;
			mGarbages.push_back(message.EventGameObject);
			break;

		case eEventOfScene::AddGameObject:			
			Assert(message.LayerType != eLayerType::End, WCHAR_IS_INVALID_TYPE);

			message.EventGameObject->initialize();
			AddGameObject(message.EventGameObject, message.LayerType);
			break;

		default:
			Assert(false, WCHAR_IS_INVALID_TYPE);
			break;
		}
	}

	mEventMessages.clear();
}

void Scene::RegisterEventAddGameObject(GameObject* const gameObject, const eLayerType LAYER_TYPE
	, const std::source_location& location)
{
	Assert(gameObject, WCHAR_IS_NULLPTR);
	Assert(LAYER_TYPE != eLayerType::End, WCHAR_IS_INVALID_TYPE);

	tEventMessageScene message = {};

	message.EventOfSceneType = eEventOfScene::AddGameObject;
	message.EventGameObject = gameObject;
	message.LayerType = LAYER_TYPE;
	message.ErrorHint = location;

	mEventMessages.push_back(message);
}

void Scene::RegisterEventSetDestroy(GameObject* const gameObject
	, const std::source_location& location)
{
	Assert(gameObject, WCHAR_IS_NULLPTR);
	Assert(gameObject->mState != GameObject::eState::Destroy, WCHAR_IS_INVALID_TYPE);

	tEventMessageScene message = {};

	message.EventOfSceneType = eEventOfScene::DestroyGameObject;
	message.EventGameObject = gameObject;
	message.ErrorHint = location;

	mEventMessages.push_back(message);
}

void Scene::AddGameObject(GameObject* const gameObject, const eLayerType LAYER_TYPE)
{
	Assert(gameObject, WCHAR_IS_NULLPTR);
	Assert(LAYER_TYPE != eLayerType::End, WCHAR_IS_INVALID_TYPE);

	gameObject->mCurLayer = LAYER_TYPE;
	mLayers[static_cast<UINT>(LAYER_TYPE)].mGameObjects.push_back(gameObject);
}

HRESULT Scene::Load(const std::wstring& FULL_PATH)
{
	Assert(false, L"");
	(void)FULL_PATH;

	return E_NOTIMPL;
}
