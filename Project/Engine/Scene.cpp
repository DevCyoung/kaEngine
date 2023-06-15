#include "pch.h"
#include "Scene.h"

namespace engine
{
	Scene::Scene()
		: mLayers()
	{
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

}