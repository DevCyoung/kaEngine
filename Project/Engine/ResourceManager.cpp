#include "pch.h"
#include "ResourceManager.h"

namespace engine
{
	ResourceManager::ResourceManager()
	{
	}

	ResourceManager::~ResourceManager()
	{
		for (HashMap& item : mResources)
		{
			memory::safe::DeleteUnorderedMap(item);
		}
	}

	void ResourceManager::initialize()
	{
		assert(!sInstance);
		sInstance = new ResourceManager();
	}
}