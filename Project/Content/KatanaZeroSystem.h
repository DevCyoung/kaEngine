#pragma once
#include <Engine/Singleton.h>
#include "KatanaScene.h"

class KatanaScene;
class GameObject;
class Camera;

enum class eKatanaSystemState
{
	None,
	Play,
	Rewind,
	CCTV,	
};

class KatanaZeroSystem
{
	friend class Content;

	SINGLETON_DECLARE(KatanaZeroSystem);
	void playBackGroundBGM(const eKatanaSceneType type);

public:
	void LoadNextScene();	
	void Rewind();
	void CCTVPlay();
	void CCTVPlayBack();
	void GameClear();

	void EnterScene(const eKatanaSceneType nextSceneType);	

	void SetCurentScene(KatanaScene* const katanaScene);
	void SetNextEffect(GameObject* const nextEffect) { mNextEffect = nextEffect; }
	void SetCRTEffect(GameObject* const crtEffect) { mCRTEffect = crtEffect; }
	void SetCRTText(GameObject* const crtText) { mCRTText = crtText; }
	void SetCRTTextTime(GameObject* const crtTextTime) { mCRTTextTime = crtTextTime; }
	void SetCRTTimeLine(GameObject* const crtTimeLine) { mCRTTimeLine = crtTimeLine; }
	void SetCRTTimeLineBar(GameObject* const crtTimeLineBar) { mCRTTimeLineBar = crtTimeLineBar; }
	void SetCRTReadyText(GameObject* const crtRaedyText) { mCRTReadyText = crtRaedyText; }
	void SetCRTBlackOut(GameObject* const crtBlackOut) { mCRTBlackOut = crtBlackOut; }

	GameObject* GetBlackOut() const { return mCRTBlackOut; }
	GameObject* GetReadyText() const { return mCRTReadyText; }

	void SetMainCamera(Camera* const mainCamera) { mMainCamera = mainCamera; }
	KatanaScene* GetCurrentScene() const;
	//KatanaScene* GetCurrentScene() const { return mCurrentScene; }

	void TurnOnCRT();
	void TurnOffCRT();

	void PlayCRT();
	void RewindCRT();
	void PauseCRT();

	void SetCRTText(const std::wstring& text);
	void SetCRTTextTime(const std::wstring& text);
	void SetCRTTimeLine(float time);

	bool IsPlayerDamaged() const { return mbPlayerDamaged; }
	void SetPlayerDamaged(const bool bPlayerDamaged) { mbPlayerDamaged = bPlayerDamaged; }

private:
	eKatanaSceneType mCurrentSceneType;
	eKatanaSystemState mSystemState;
	Camera* mMainCamera;

	GameObject* mNextEffect;

	//CRT
	GameObject* mCRTEffect;
	GameObject* mCRTText;
	GameObject* mCRTTextTime;
	GameObject* mCRTTimeLine;
	GameObject* mCRTTimeLineBar;
	GameObject* mCRTReadyText;
	GameObject* mCRTBlackOut;

	bool mbPlayerDamaged;
};

#define gKatanaZeroSystem KatanaZeroSystem::GetInstance()