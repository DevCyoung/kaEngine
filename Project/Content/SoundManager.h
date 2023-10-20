#pragma once

#include "ResourceManager.h"

class SoundManager
{
public:
	static void initialize()
	{
		Assert(!sInstance, WCHAR_IS_NOT_NULLPTR);
		sInstance = new SoundManager();
	}

	static void deleteInstance()
	{
		Assert(sInstance, WCHAR_IS_NULLPTR);
		delete sInstance;
		sInstance = nullptr;
	}

	static SoundManager* GetInstance()
	{
		Assert(sInstance, WCHAR_IS_NULLPTR);
		return sInstance;
	}

public:
	SoundManager();
	virtual ~SoundManager();
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	void Play(eResAudioClip audioClip);
	void Play(eResAudioClip audioClip, float volume);
	void Play(eResAudioClip audioClip, float volume, bool loop);

	void Stop(eResAudioClip audioClip);

	AudioClip* PlayBackGround(eResAudioClip audioClip);
	AudioClip* PlayBackGround(eResAudioClip audioClip, float volume);

	void PlayInForce(eResAudioClip audioClip, float volume);

	void SetVolume(eResAudioClip audioClip, float volume);
	void SetPitch(eResAudioClip audioClip, float pitch);	

	void TurnOnSound();
	void TurnOffSound();

	void SetSoundPitch(float fitch);

private:
	AudioClip* getClip(eResAudioClip audioClip);

private:
	inline static SoundManager* sInstance = nullptr;
	bool mbSoundOn;
	float mPitch;
	bool mbFitch;
	GameObject* mMainCamera;
	Scene* mScene;

	eResAudioClip backgroundClip;
};

