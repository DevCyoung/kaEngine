#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "MessageManager.h"
#include "RenderTargetRenderer.h"
#include "Physics2D.h"
#include "CollisionManagement2D.h"
#include "GameSystem.h"

Scene::Scene()
	: mCollisionManagement2D(new CollisionManagement2D())
	, mGameSystem(new GameSystem(this))
	, mLayers()
	, mEventMessages()
	, mGarbages()	
	, mBackgroundColor(Vector4(0.4f, 0.4f, 0.4f, 1.f))
{
	mEventMessages.reserve(100);
	mGarbages.reserve(100);

	mCollisionManagement2D->TurnOnAllCollisionLayer();	
	mCollisionManagement2D->TurnOffCollisionLayer(eLayerType::Bullet, eLayerType::Bullet);
	mCollisionManagement2D->TurnOffCollisionLayer(eLayerType::Bullet, eLayerType::Mouse);
}

Scene::~Scene()
{
	SAFE_DELETE_POINTER(mGameSystem);
	SAFE_DELETE_POINTER(mCollisionManagement2D);
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

void Scene::fixedUpdate()
{
	for (Layer& layer : mLayers)
	{
		layer.fixedUpdate();
	}
}


void Scene::lateUpdate()
{
	size_t gameObjectCount = 0;

	for (Layer& layer : mLayers)
	{
		layer.lateUpdate();

		gameObjectCount += layer.mGameObjects.size();
	}

	if (MessageManager::GetInstance()->IsAddTitleMessage())
	{
		constexpr UINT WSTR_LEN = 256;
		wchar_t buff[WSTR_LEN] = { 0, };
		swprintf_s(buff, WSTR_LEN, L"<GameObject Count : %zu>", gameObjectCount);
		MessageManager::GetInstance()->AddTitleMessage(buff);
	}

	//面倒贸府
	mCollisionManagement2D->phisicsUpdate(this);
	
	//面倒焊埃
	for (Layer& layer : mLayers)
	{
		layer.lastUpdate();
	}

	//if exist garbage, remove it, No rendering
	if (false == mGarbages.empty())
	{
		for (Layer& layer : mLayers)
		{
			std::vector<GameObject*>& gameObjects = layer.mGameObjects;
			gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
				[](const GameObject* const gameObject)
				{
					return GameObject::eState::Destroy == gameObject->mState;
				}), gameObjects.end());
		}
	}
}

void Scene::render(const UINT renderTargetWidth,
	const UINT renderTargetHeight,
	ID3D11RenderTargetView** const ppRenderTargetView,
	ID3D11DepthStencilView* const depthStencilView) const
{
	mGameSystem->GetRenderTargetRenderer()->Render(renderTargetWidth,
		renderTargetHeight,		
		ppRenderTargetView,
		depthStencilView);
}

void Scene::renderFlush()
{
	mGameSystem->GetRenderTargetRenderer()->flush();
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
			//Assert(message.EventGameObject->mState != GameObject::eState::Destroy, WCHAR_IS_INVALID_TYPE);

			if (message.EventGameObject->mState != GameObject::eState::Destroy)
			{
				message.EventGameObject->mState = GameObject::eState::Destroy;
				mGarbages.push_back(message.EventGameObject);
			}

			break;

		case eEventOfScene::AddGameObject:
			Assert(message.LayerType != eLayerType::End, WCHAR_IS_INVALID_TYPE);

			AddGameObject(message.EventGameObject, message.LayerType);
			message.EventGameObject->initialize();
			break;

		default:
			Assert(false, WCHAR_IS_INVALID_TYPE);
			break;
		}
	}

	mEventMessages.clear();
}

void Scene::RegisterEventAddGameObject(GameObject* const gameObject,
	const eLayerType layerType, const std::source_location& location)
{
	Assert(gameObject, WCHAR_IS_NULLPTR);
	Assert(layerType != eLayerType::End, WCHAR_IS_INVALID_TYPE);

	tEventMessageScene message = {};

	message.EventOfSceneType = eEventOfScene::AddGameObject;
	message.EventGameObject = gameObject;
	message.LayerType = layerType;
	message.ErrorHint = location;

	mEventMessages.push_back(message);
}

void Scene::RegisterEventSetDestroy(GameObject* const gameObject
	, const std::source_location& location)
{
	Assert(gameObject, WCHAR_IS_NULLPTR);
	if (gameObject->mState == GameObject::eState::Destroy)
	{
		return;
	}

	Assert(gameObject->mState != GameObject::eState::Destroy, WCHAR_IS_INVALID_TYPE);

	tEventMessageScene message = {};
	message.EventOfSceneType = eEventOfScene::DestroyGameObject;
	message.EventGameObject = gameObject;
	message.ErrorHint = location;

	mEventMessages.push_back(message);
}

void Scene::AddGameObject(GameObject* const gameObject, const eLayerType layerType)
{
	Assert(gameObject, WCHAR_IS_NULLPTR);
	Assert(layerType != eLayerType::End, WCHAR_IS_INVALID_TYPE);
	Assert(mGameSystem, WCHAR_IS_NULLPTR);

	gameObject->mLayerType = layerType;
	gameObject->mGameSystem = mGameSystem;
	mLayers[static_cast<UINT>(layerType)].mGameObjects.push_back(gameObject);
}

HRESULT Scene::Load(const std::wstring& filePath)
{
	Assert(false, L"");
	(void)filePath;

	return E_NOTIMPL;
}
