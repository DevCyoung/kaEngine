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
#include "SimpleEditorCollider2D.h"
Chinatown01Scene::Chinatown01Scene()
{
	SetBackgroundColor(Vector4(0.5294f, 0.5254f, 0.7843f, 1.f));

	mCollisionManagement2D->TurnOffAllCollisionLayer();
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::LeftSlope);

#pragma region Material
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
#pragma endregion

#pragma region MapObj
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
#pragma endregion

#pragma region Editor
	//{
	//	GameObject* const testObj = new GameObject();
	//	testObj->AddComponent<SimpleEditorCollider2D>();
	//	AddGameObject(testObj, eLayerType::Default);
	//}
#pragma endregion

#pragma region WallObj
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-2224, 496, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(96, 416));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1888, 352, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(768, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1632, 656, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(1280, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1024, 816, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 544));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1856, 800, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 512));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-160, 80, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(2112, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(48, 624, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(544, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-64, 368, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(320, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(560, 368, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(672, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(560, 736, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(160, 768));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(176, 1104, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(800, 352));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-192, 1056, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 448));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-224, 976, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 224));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-256, 1024, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-192, 496, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 288));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-240, 624, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(32, 160));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1056, 384, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(128, 64));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1024, 336, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 160));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-192, 352, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 192));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(256, 320, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-1504.000000, 416.000000, -1216.000000, 128.000000);
		AddGameObject(wall, eLayerType::LeftSlope);
	}
#pragma endregion


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
		GameObjectBuilder::InstantiateGlobalLight2D(this, eLayerType::Default);
	}

	{
		GameObject* player =  GameObjectBuilder::InstantiatePlayer(this);
		player->GetComponent<Transform>()->SetPosition(-2000, 464, 0);
	}

	{
		//GameObjectBuilder::AddUI(this);
		GameObjectBuilder::AddCamera(this);
	}
}

Chinatown01Scene::~Chinatown01Scene()
{
}

