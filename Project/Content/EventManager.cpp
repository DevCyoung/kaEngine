#include "pch.h"
#include "EventManager.h"
#include <Engine/TimeManager.h>

EventManager::EventManager()
	: mbTimeEffect(false)
	, mTimeEffectDuration(0.f)
	, mTimeEffectTimeScale(1.f)
{
}

EventManager::~EventManager()
{
}

void EventManager::ShotTimeEffect(const float timeScale, const float duration)
{
	mbTimeEffect = true;
	mTimeEffectDuration = duration;
	mTimeEffectTimeScale = timeScale;

	TimeManager::GetInstance()->SetTileScale(timeScale);
}

void EventManager::LateUpdate()
{
	if (mbTimeEffect)
	{
		mTimeEffectDuration -= gRealDeltaTime;

		if (mTimeEffectDuration <= 0.f)
		{
			mbTimeEffect = false;
			mTimeEffectDuration = 0.f;
			mTimeEffectTimeScale = 1.f;

			TimeManager::GetInstance()->SetTileScale(1.f);
		}
	}
}
