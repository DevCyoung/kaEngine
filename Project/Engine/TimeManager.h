#pragma once

#include "Engine.h"
#include "Singleton.h"

namespace engine
{
    class TimeManager
    {	
		friend class Engine;
		SINGLETON_DECLARE(TimeManager);

	private:
		void update();
		void render();

	public:
		float GetDeltaTime() const { return mDeltaTime; }

	private:
		float mDeltaTime;
		float mSecond;
		LARGE_INTEGER mCpuFrequency;
		LARGE_INTEGER mPrevFrequency;
		LARGE_INTEGER mCurFrequency;
    };	
}

#define gDeltaTime engine::TimeManager::GetInstance()->GetDeltaTime()