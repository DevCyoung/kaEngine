#include "pch.h"
#include "Scene.h"


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

void Scene::render()
{
	for (Layer& layer : mLayers)
	{
		layer.render();
	}
}

HRESULT Scene::Load(const std::wstring& path)
{
	(void)path;

	Assert(false, L"");

	return E_NOTIMPL;
}