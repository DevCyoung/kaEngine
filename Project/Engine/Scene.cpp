#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

#include "Shader.h"

namespace engine
{
	Scene::Scene()
		: mLayers()
	{
	}

	Scene::~Scene()
	{
		for (Layer* const layer : mLayers)
		{
			delete layer;			
		}		
	}

	void Scene::initialize()
	{
		mLayers.push_back(new Layer);

		for (Layer* const layer : mLayers)
		{
			layer->initialize();
		}		
	}

	void Scene::update()
	{
		for (Layer* const layer : mLayers)
		{
			layer->update();
		}
	}

	void Scene::lateUpdate()
	{
		for (Layer* const layer : mLayers)
		{
			layer->lateUpdate();
		}
	}

	void Scene::render(/*mGraphicDevice*/)
	{
		for (Layer* const layer : mLayers)
		{
			layer->render(/*mGraphicDevice*/);
		}
	}

}