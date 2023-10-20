#include "pch.h"
#include "EventManager.h"
#include <Engine/TimeManager.h>

EventManager::EventManager()
	: mbTimeEffect(false)
	, mTimeEffectDuration(0.f)
	, mTimeEffectTimeScale(1.f)
	, mbSlomo(false)
{
}

EventManager::~EventManager()
{
}

void EventManager::ShotTimeEffect(const float timeScale, const float duration, eTimeEffectType type)
{		
	if (mbSlomo)
	{

		return;
	}

	if (!mTimeEffects.empty())
	{
		//slomo중인데 damaged가 들어오면 damaged는 무시
		if (mTimeEffects.front().type == eTimeEffectType::Slomo &&
			type == eTimeEffectType::Damaged)
		{
			return;
		}
	}

	tTimeEffect timeEffect = {};

	timeEffect.type = type;
	timeEffect.Duration = duration;
	timeEffect.TimeScale = timeScale;
	
	mTimeEffects.push(timeEffect);
}

void EventManager::LateUpdate()
{
	if (mTimeEffects.empty())
	{
		return;
	}

	tTimeEffect& timeEffect = mTimeEffects.front();
	timeEffect.Duration -= gRealDeltaTime;

	TimeManager::GetInstance()->SetTileScale(timeEffect.TimeScale);

	if (timeEffect.Duration <= 0.f)
	{
		mTimeEffects.pop();
		TimeManager::GetInstance()->SetTileScale(1.f);
	}	
}
