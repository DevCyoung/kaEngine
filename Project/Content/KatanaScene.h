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
#include "NexeScene.h"

class KatanaScene : public Scene
{
public:
	KatanaScene();
	virtual ~KatanaScene();
	KatanaScene(const KatanaScene&) = delete;
	KatanaScene& operator=(const KatanaScene&) = delete;

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


	virtual Scene* Clone() = 0;
	virtual Scene* NextScene() = 0;

protected:
	virtual void initialize() final;
	virtual void update() final;
	virtual void lateUpdate() final;

	// Scene을(를) 통해 상속됨
	
};

