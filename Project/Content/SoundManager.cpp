#include "pch.h"
#include "SoundManager.h"
#include "Components.h"
#include "ResourceManager.h"
#include <Engine/Scene.h>
#include <Engine/GameObject.h>

SoundManager::SoundManager()
	: mMainCamera(nullptr)
	, mScene(nullptr)
	, mbSoundOn(true)
	, mbFitch(false)
	, mPitch(1.f)
{
}

SoundManager::~SoundManager()
{
}

AudioClip* SoundManager::getClip(eResAudioClip audioClip)
{
	AudioClip* clip = gResourceManager->FindOrNull<AudioClip>(EnumResourcePath(audioClip));

	if (clip == nullptr)
	{
		gResourceManager->Load<AudioClip>(EnumResourcePath(audioClip));
		clip = gResourceManager->Find<AudioClip>(EnumResourcePath(audioClip));
	}

	return clip;
}


void SoundManager::Play(eResAudioClip audioClip)
{	
	AudioClip* clip = getClip(audioClip);

	if (mbSoundOn)
	{
		clip->Play();

		//clip->SetPitch(mPitch);
	}	
}

void SoundManager::BackGround(eResAudioClip audioClip)
{
	AudioClip* clip = getClip(audioClip);

	clip->SetLoop(true);
	clip->Play();
}

void SoundManager::Play(eResAudioClip audioClip, float volume)
{
	AudioClip* clip = getClip(audioClip);

	if (mbSoundOn)
	{
		clip->Play();
		clip->SetVolume(volume);

		//clip->SetPitch(mPitch);
	}	
}

void SoundManager::Play(eResAudioClip audioClip, float volume, bool loop)
{
	AudioClip* clip = getClip(audioClip);	

	if (mbSoundOn)
	{
		clip->Play();
		clip->SetVolume(volume);
		clip->SetLoop(loop);

		//clip->SetPitch(mPitch);
	}
}

void SoundManager::Stop(eResAudioClip audioClip)
{
	AudioClip* clip = getClip(audioClip);

	clip->Stop();
}

void SoundManager::BackGround(eResAudioClip audioClip, float volume)
{
	AudioClip* clip = getClip(audioClip);

	clip->SetLoop(true);
	clip->Play();
	clip->SetVolume(volume);
}

void SoundManager::PlayInForce(eResAudioClip audioClip, float volume)
{
	AudioClip* clip = getClip(audioClip);

	clip->Play();
	clip->SetVolume(volume);
}

void SoundManager::SetVolume(eResAudioClip audioClip, float volume)
{
	AudioClip* clip = getClip(audioClip);

	clip->SetVolume(volume);
}

void SoundManager::SetPitch(eResAudioClip audioClip, float pitch)
{
	AudioClip* clip = getClip(audioClip);

	clip->SetPitch(pitch);
}

void SoundManager::TurnOnSound()
{
	mbSoundOn = true;
}

void SoundManager::TurnOffSound()
{
	mbSoundOn = false;
}

void SoundManager::SetSoundPitch(float fitch)
{
	mPitch = fitch;

	for (int i = 0; i < static_cast<int>(eResAudioClip::End); i++)
	{
		eResAudioClip clipType = static_cast<eResAudioClip>(i);
		AudioClip* clip = getClip(clipType);

		clip->SetPitch(fitch);
	}	
}

