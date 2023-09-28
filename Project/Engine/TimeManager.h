#pragma once
#include "Singleton.h"

class TimeManager
{
	friend class Engine;	
	friend class Content;
	SINGLETON_DECLARE(TimeManager);

private:
	void update();	

public:
	float GetDeltaTime() const { return mDeltaTime; }
	float GetGlobalTime() const { return mGlobalTime; }

	void StartTime(LARGE_INTEGER* const starTime);
	float EndTime(LARGE_INTEGER* const starTime);

	float GetTileScale() const { return mTimeScale; }
	void SetTileScale(const float tileScale) { mTimeScale = tileScale; }


private:
	float mDeltaTime;
	float mGlobalTime;
	float mSecond;
	float mTimeScale;

	LARGE_INTEGER mCpuFrequency;
	LARGE_INTEGER mPrevFrequency;
	LARGE_INTEGER mCurFrequency;
};

#define gDeltaTime TimeManager::GetInstance()->GetDeltaTime()
#define gGlobalTime TimeManager::GetInstance()->GetGlobalTime()