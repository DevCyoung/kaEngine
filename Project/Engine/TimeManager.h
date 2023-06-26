#pragma once
#include "Singleton.h"


class TimeManager
{
	friend class Engine;
	SINGLETON_DECLARE(TimeManager);

private:
	void update();	

public:
	float GetDeltaTime() const { return mDeltaTime; }

private:
	float mDeltaTime;
	float mSecond;
	LARGE_INTEGER mCpuFrequency;
	LARGE_INTEGER mPrevFrequency;
	LARGE_INTEGER mCurFrequency;
};

#define gDeltaTime TimeManager::GetInstance()->GetDeltaTime()