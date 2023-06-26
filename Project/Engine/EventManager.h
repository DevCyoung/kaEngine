#pragma once
#include "Singleton.h"
#include "eEventType.h"


class EventManager
{
	friend class Engine;
	SINGLETON_DECLARE(EventManager);

private:
	void update();
	void lateUpdate();
};