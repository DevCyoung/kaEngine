#pragma once

struct tTimeEffect
{
	float TimeScale;
	float Duration;
};

class EventManager
{
public:
	EventManager();
	virtual ~EventManager();
	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;

	void ShotTimeEffect(const float tileScale, const float duration);

	void LateUpdate();

	bool mbTimeEffect;
	float mTimeEffectDuration;
	float mTimeEffectTimeScale;

	std::queue<tTimeEffect> mTimeEffects;
};

