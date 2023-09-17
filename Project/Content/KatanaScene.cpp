#include "pch.h"
#include "KatanaScene.h"
#include "TItleScene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include "CameraInputMoveMent.h"
#include "CursorMovement.h"
#include "UIEffect.h"
#include "Bugiman.h"
#include "PlayerMovementTest.h"
#include "ShiftController.h"
#include <Engine/Engine.h>
#include <Engine/SceneManager.h>
#include <Engine/EngineMath.h>
#include "LerpTest.h"
#include <Engine/CollisionManagement2D.h>
#include "InputMovementTest.h"
#include "ChildTest.h"
#include "ParentTest.h"
#include "NoiseTest.h"
#include "PlayerController.h"
#include "PlayerFSM.h"
#include "GridPainter.h"
#include <Engine/Color.h>
#include "PickPixelTest.h"
#include "Rect2DInterpolation.h"
#include "SimpleEditorCollider2D.h"
#include "GameManager.h"
#include "PathNode.h"

KatanaScene::KatanaScene()
{
	mCollisionManagement2D->TurnOffAllCollisionLayer();
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Platform);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Platform);

	//PathNode

	GameManager::initialize();

	GameManager::GetInstance()->GetRewindManager()->SetRewindState(eRewindState::Record);
}

KatanaScene::~KatanaScene()
{
	GameManager::deleteInstance();
}

void KatanaScene::lateUpdate()
{
	Scene::lateUpdate();

	GameManager::GetInstance()->GetRewindManager()->LateUpdate();
}
