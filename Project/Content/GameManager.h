#pragma once
#include <Engine/Singleton.h>

class GameObject;

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
	GameObject* const GetPlayer() const { return mPlayer; }

private:
	inline static GameManager* sInstance = nullptr;
	GameObject* mPlayer;
};
