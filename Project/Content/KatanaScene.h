#pragma once
#include <Engine/Scene.h>
#include <Engine/CollisionManagement2D.h>
#include <Engine/Color.h>
#include <Engine/ConstantBuffer.h>
#include <Engine/Engine.h>
#include <Engine/EngineMath.h>
#include <Engine/SceneManager.h>
#include <Engine/GraphicDeviceDx11.h>

#include "Components.h"
#include "CameraInputMoveMent.h"
#include "CursorMovement.h"
#include "CameraWall.h"
#include "GameObjectBuilder.h"
#include "GameManager.h"
#include "MaterialBuilder.h"
#include "PlayerController.h"
#include "PlayerFSM.h"
#include "PathNode.h"
#include "PickPixelTest.h"
#include "ResourceManager.h"
#include "Rect2DInterpolation.h"
#include "RewindComponent.h"
#include "ShiftController.h"
#include "SimpleEditorCollider2D.h"
#include "UIEffect.h"
#include "ClearController.h"

enum class eKatanaSceneType
{
	None,
	Title,
	ChinaTown01,
	ChinaTown04,
	ChinaTown05,
	HeadHunter,
	Kissyface,
};

class KatanaScene : public Scene
{
public:
	KatanaScene(const eKatanaSceneType type);
	virtual ~KatanaScene();
	KatanaScene(const KatanaScene&) = delete;
	KatanaScene& operator=(const KatanaScene&) = delete;

	eKatanaSceneType GetKatanaSceneType() const { return mKatanaSceneType; }

	virtual void SetDefaultCollision();

	virtual void AddMapObject() = 0;
	virtual void AddWallObject() = 0;
	virtual void AddDoorObject() = 0;
	virtual void AddMonsterObject() = 0;
	virtual void AddObject() = 0;
	virtual void AddLightObject() = 0;
	virtual void AddCameraObject() = 0;
	virtual void AddUIObject() = 0;
	virtual void AddPlayerObject() = 0;

	GameObject* InstantiateMonster(eMonsterType type, Vector2 pos, bool bFlipX = false);
	GameObject* InstantiateText(const wchar_t* wstr, XMUINT2 pos, float scale, XMUINT4 color);

	virtual Scene* Clone() = 0;
	virtual KatanaScene* GetNextScene() = 0;

	virtual void enter();



	bool IsClear() { return mEnemyCount == 0; }
	void AddEnemyCount()  { mEnemyCount++; }
	void SubEnemyCount()  { mEnemyCount--; }

protected:
	virtual void initialize() final;
	virtual void update() final;
	virtual void lateUpdate() final;

	int mEnemyCount;

	// Scene을(를) 통해 상속됨
	eKatanaSceneType mKatanaSceneType;
};

