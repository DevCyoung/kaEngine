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

void Scene::AddGameObject(GameObject* const obj, const eLayerType type)
{
	Assert(obj, WCHAR_IS_NULLPTR);

	obj->mCurLayer = type;
	mLayers[static_cast<int>(type)].AddGameObject(obj);
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

HRESULT Scene::Load(const std::wstring& path)
{
	(void)path;

	Assert(false, L"");

	return E_NOTIMPL;
}