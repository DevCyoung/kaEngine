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

