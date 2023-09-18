#include "pch.h"
#include "GameManager.h"
#include <Engine/GameObject.h>

GameManager::GameManager()
	: mPlayer(nullptr)
	, mPathInfo(nullptr)
	, mRewindManager(nullptr)
{		
	mPathInfo = new PathInfo();
	mRewindManager = new RewindManager();
}

GameManager::~GameManager()
{
	SAFE_DELETE_POINTER(mPathInfo);
	SAFE_DELETE_POINTER(mRewindManager);
}
