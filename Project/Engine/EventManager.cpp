#include "pch.h"
#include "EventManager.h"

namespace engine
{
	EventManager::EventManager()
	{
	}

	EventManager::~EventManager()
	{
	}

	void EventManager::initialize()
	{
		assert(!sInstance);
		sInstance = new EventManager();
	}

	void EventManager::update()
	{
	}

	void EventManager::lateUpdate()
	{
	}
}