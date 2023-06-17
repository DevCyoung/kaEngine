#include "pch.h"
#include "ResourceManager.h"

namespace engine
{
	ResourceManager::ResourceManager()
	{

	}

	ResourceManager::~ResourceManager()
	{
		for (std::unordered_map<UINT, Resource*>& item : mResources)
		{
			safe::DeleteUnorderedMap(item);
		}		
	}

	void ResourceManager::initialize()
	{
		assert(!sInstance);
		sInstance = new ResourceManager();
	}
}