#include "pch.h"
#include "GameManager.h"
#include <Engine/GameObject.h>
#include "Components.h"
#include <Engine/GameObject.h>

GameManager::GameManager()
	: mPlayer(nullptr)
	, mUITimer(nullptr)
	, mPathInfo(nullptr)
	, mRewindManager(nullptr)
	//, mSoundManager(nullptr)
	, mEffectManager(nullptr)
	, mEventManager(nullptr)

{		
	mPathInfo = new PathInfo();
	mRewindManager = new RewindManager();
	//mSoundManager = new SoundManager();	
	mEffectManager = new EffectManager();	
	mEventManager = new EventManager();
}

GameManager::~GameManager()
{
	SAFE_DELETE_POINTER(mPathInfo);
	SAFE_DELETE_POINTER(mRewindManager);
	//SAFE_DELETE_POINTER(mSoundManager);
	SAFE_DELETE_POINTER(mEffectManager);
	SAFE_DELETE_POINTER(mEventManager);
}
