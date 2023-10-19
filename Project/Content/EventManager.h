#pragma once

enum class eTimeEffectType
{
	None,
	Slomo,
	Damaged,
};

struct tTimeEffect
{
	eTimeEffectType type;
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

	void ShotTimeEffect(const float tileScale, const float duration, eTimeEffectType type);

	void LateUpdate();

	void SetSlomo(bool slomo) 
	{ 
		mbSlomo = slomo; 

		while (!mTimeEffects.empty())
		{
			mTimeEffects.pop();
		}
	}

	bool mbTimeEffect;
	float mTimeEffectDuration;
	float mTimeEffectTimeScale;

	bool mbSlomo;

	std::queue<tTimeEffect> mTimeEffects;
};

