#include "pch.h"
#include "GameManager.h"
#include <Engine/GameObject.h>

GameManager::GameManager()
	: mPlayer(nullptr)
	, mPathInfo(nullptr)
{		
	mPathInfo = new PathInfo();
}

GameManager::~GameManager()
{
	SAFE_DELETE_POINTER(mPathInfo);
}
