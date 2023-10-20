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
	, mEffectManager(nullptr)
	, mEventManager(nullptr)
	, mTimeController(nullptr)

{		
	mPathInfo = new PathInfo();
	mRewindManager = new RewindManager();	
	mEffectManager = new EffectManager();	
	mEventManager = new EventManager();
	mTimeController = new TimeController();
}

GameManager::~GameManager()
{
	SAFE_DELETE_POINTER(mPathInfo);
	SAFE_DELETE_POINTER(mRewindManager);	
	SAFE_DELETE_POINTER(mEffectManager);
	SAFE_DELETE_POINTER(mEventManager);
	SAFE_DELETE_POINTER(mTimeController);
}
