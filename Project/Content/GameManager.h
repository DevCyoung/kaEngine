#pragma once
#include <Engine/Singleton.h>
#include "PathInfo.h"

class GameObject;
class PathInfo;

class GameManager
{
public:
	static void initialize()
	{
		Assert(!sInstance, WCHAR_IS_NOT_NULLPTR);
		sInstance = new GameManager();
	}

	static void deleteInstance()
	{
		Assert(sInstance, WCHAR_IS_NULLPTR);
		delete sInstance;
		sInstance = nullptr;
	}

	static GameManager* GetInstance()
	{
		Assert(sInstance, WCHAR_IS_NULLPTR);
		return sInstance;
	}

	GameManager();
	virtual ~GameManager();
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

public:
	void SetPlayer(GameObject* const player) { this->mPlayer = player; }
	//void SetPathInfo(PathInfo* const pathInfo) { this->mPathInfo = pathInfo; }

	GameObject* const GetPlayer() const { return mPlayer; }
	PathInfo* const GetPathInfo() const { return mPathInfo; }

private:
	inline static GameManager* sInstance = nullptr;
	GameObject* mPlayer;
	PathInfo* mPathInfo;
};
