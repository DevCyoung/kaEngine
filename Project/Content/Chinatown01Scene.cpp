#include "pch.h"
#include "Chinatown01Scene.h"
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

Chinatown01Scene::Chinatown01Scene()
{
	SetBackgroundColor(Vector4(0.5294f, 0.5254f, 0.7843f, 1.f));

	mCollisionManagement2D->TurnOffAllCollisionLayer();
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Default);

	{
		Material* const material =
			MaterialBuilder::Sprite2D(eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_spr_chinatown_parallax_1);
		gResourceManager->Insert(L"Chanatown05BackGround01", material);
	}
	
	{
		Material* const material =
			MaterialBuilder::Sprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_spr_chinatown_parallax_2);
		gResourceManager->Insert(L"Chanatown05BackGround02", material);
	}

	{
		Material* const material =
			MaterialBuilder::Sprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_spr_chinatown_parallax_3);
		gResourceManager->Insert(L"Chanatown05BackGround03", material);
	}

	{
		Material* const material =
			MaterialBuilder::Sprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown01_Tilemap);
		gResourceManager->Insert(L"Chanatown01TileMap", material);
	}

	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"Chanatown05BackGround01");
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
		obj->GetComponent<Transform>()->SetPosition(-580, 560.f, 500.f);

		AddGameObject(obj, eLayerType::BackGround);
	}

	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"Chanatown05BackGround02");

		obj->GetComponent<Transform>()->SetScale(2.5f, 2.5f, 1.f);
		obj->GetComponent<Transform>()->SetPosition(-640, 560.f, 600.f);

	
		AddGameObject(obj, eLayerType::BackGround);
	}

	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"Chanatown05BackGround03");

		obj->GetComponent<Transform>()->SetScale(2.5f, 2.5f, 1.f);
		obj->GetComponent<Transform>()->SetPosition(-640, 560.f, 700.f);
	
		AddGameObject(obj, eLayerType::BackGround);
	}

	{
		GameObject* const testObj = new GameObject();
		
		testObj->AddComponent<RectCollider2D>();
		testObj->SetName(L"Wall");
		
		testObj->GetComponent<RectCollider2D>()->SetSize(1000.f, 100.f);
		testObj->GetComponent<Transform>()->SetPosition(0.f, -300.f, 1.f);
		
		AddGameObject(testObj, eLayerType::Default);
	}

	//tile map
	{
		GameObject* const tile = GameObjectBuilder::Default2D(L"Chanatown01TileMap");
		tile->AddComponent<GridPainter>();		

		tile->GetComponent<GridPainter>()->SetCellSize(32);
		tile->GetComponent<GridPainter>()->SetCellCount(XMUINT2(200, 200));
		tile->GetComponent<GridPainter>()->SetColor(helper::Color::YELLOW);
		tile->GetComponent<GridPainter>()->TurnOffDraw();
		
		AddGameObject(tile, eLayerType::TileMap);
	}

	{
		GameObject* const player = GameObjectBuilder::Player();

		AddGameObject(player, eLayerType::Default);
	}

	{
		GameObjectBuilder::AddUI(this);
		GameObjectBuilder::AddCamera(this);
	}	
}

Chinatown01Scene::~Chinatown01Scene()
{
}
