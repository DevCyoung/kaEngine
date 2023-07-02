#include "pch.h"
#include "ResourceManager.h"
#include "Engine.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (Dictionary& item : mResources)
	{
		memory::safe::DeleteUnorderedMap(item);		
	}
}
