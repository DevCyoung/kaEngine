#pragma once
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
};

