#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
	: mLayers()
{
}

Scene::~Scene()
{
}

void Scene::AddGameObject(GameObject* const obj, const eLayerType LAYER_TYPE)
{
	Assert(obj, WCHAR_IS_NULLPTR);

	obj->mCurLayer = LAYER_TYPE;
	mLayers[static_cast<int>(LAYER_TYPE)].AddGameObject(obj);
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
	for (Layer& layer : mLayers)
	{
		layer.lateUpdate();
	}
}

HRESULT Scene::Load(const std::wstring& FULL_PATH)
{
	(void)FULL_PATH;

	Assert(false, L"");

	return E_NOTIMPL;
}