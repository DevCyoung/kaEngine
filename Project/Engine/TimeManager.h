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
	float GetGlobalTime() const { return mGlobalTime; }

	void StartTime(LARGE_INTEGER* const starTime);
	float EndTime(LARGE_INTEGER* const starTime);

private:
	float mDeltaTime;
	float mGlobalTime;
	float mSecond;

	LARGE_INTEGER mCpuFrequency;
	LARGE_INTEGER mPrevFrequency;
	LARGE_INTEGER mCurFrequency;
};

#define gDeltaTime TimeManager::GetInstance()->GetDeltaTime()
#define gGlobalTime TimeManager::GetInstance()->GetGlobalTime()