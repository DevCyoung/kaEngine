#pragma once
#include "Singleton.h"
#include "eEventType.h"

namespace engine
{
	class EventManager
	{
		friend class Engine;
		SINGLETON_DECLARE(EventManager);

	private:
		void update();
		void lateUpdate();
	};
}