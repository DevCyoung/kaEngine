#include "pch.h"
#include "Chinatown04Scene.h"
#include "Components.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include <Engine/CollisionManagement2D.h>
#include "SimpleEditorCollider2D.h"

Chinatown04Scene::Chinatown04Scene()
{
	mCollisionManagement2D->TurnOffAllCollisionLayer();
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::LeftSlope);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::RightSlope);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Platform);

#pragma region Material
	{
		Material* const tileMaterial =
			MaterialBuilder::LightSprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown04_Tilemap);
		gResourceManager->Insert(L"Chanatown04TileMap", tileMaterial);
	}
#pragma endregion

#pragma region MapObj

	{
		GameObject* const tile = GameObjectBuilder::Default2D(L"Chanatown04TileMap");
		//tile->AddComponent<Chinatown04Controller>();

		AddGameObject(tile, eLayerType::Default);
	}
#pragma endregion

#pragma region Editor
	//{
	//	GameObject* const testObj = new GameObject();
	//	testObj->AddComponent<SimpleEditorCollider2D>();
	//	AddGameObject(testObj, eLayerType::Default);
	//}
#pragma endregion

#pragma region ColliderObj



	//Wall
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(192, 48, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 160));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-128, 336, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 160));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-512, 688, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 288));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(192, 688, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 288));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0, 672, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(2304, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1056, 496, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(192, 672));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-960, 256, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(384, 320));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-384, 384, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(448, 64));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(256, 384, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(448, 64));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-656, 80, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(224, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(384, -224, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(1280, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(400, 96, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(352, 64));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(944, 384, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(160, 64));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(1056, 544, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(192, 384));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-64, 96, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(192, 64));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(800, 96, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(448, 64));
		AddGameObject(wall, eLayerType::Wall);
	}




	//Slope
	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-544, 128, -256, -160);
		AddGameObject(wall, eLayerType::LeftSlope);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(864, 416, 576, 128);

		AddGameObject(wall, eLayerType::RightSlope);
	}




	//Platform
	{
		GameObject* const platform = new GameObject();
		//[LineCollider]
		platform->AddComponent<LineCollider2D>();
		platform->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		platform->GetComponent<LineCollider2D>()->SetPoints(-544, 128, -160, 128);
		AddGameObject(platform, eLayerType::Platform);
	}

	{
		GameObject* const platform = new GameObject();
		//[LineCollider]
		platform->AddComponent<LineCollider2D>();
		platform->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		platform->GetComponent<LineCollider2D>()->SetPoints(-768, 416, -608, 416);
		AddGameObject(platform, eLayerType::Platform);
	}

	{
		GameObject* const platform = new GameObject();
		//[LineCollider]
		platform->AddComponent<LineCollider2D>();
		platform->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		platform->GetComponent<LineCollider2D>()->SetPoints(-96, 416, 32, 416);
		AddGameObject(platform, eLayerType::Platform);
	}

	{
		GameObject* const platform = new GameObject();
		//[LineCollider]
		platform->AddComponent<LineCollider2D>();
		platform->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		platform->GetComponent<LineCollider2D>()->SetPoints(32, 128, 160, 128);
		AddGameObject(platform, eLayerType::Platform);
	}

	{
		GameObject* const platform = new GameObject();
		//[LineCollider]
		platform->AddComponent<LineCollider2D>();
		platform->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		platform->GetComponent<LineCollider2D>()->SetPoints(480, 416, 864, 416);
		AddGameObject(platform, eLayerType::Platform);
	}

	//Small Triangle
	{
		//4pixel interpolate
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//wall->GetComponent<LineCollider2D>()->SetPoints(-224, 64, -160, 128); original
		wall->GetComponent<LineCollider2D>()->SetPoints(-220, 68, -160, 128);
		AddGameObject(wall, eLayerType::RightSlope);
	}
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-192, 66.5, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 5));
		AddGameObject(wall, eLayerType::Wall);
	}


	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//wall->GetComponent<LineCollider2D>()->SetPoints(480, 416, 544, 352); original
		wall->GetComponent<LineCollider2D>()->SetPoints(480, 416, 540, 356);
		AddGameObject(wall, eLayerType::LeftSlope);
	}
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(512, 354.5, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 5));
		AddGameObject(wall, eLayerType::Wall);
	}



	//CameraWall
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-1072, 224, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(224, 1664));
		AddGameObject(wall, eLayerType::CamearaWall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-16, 848, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(2336, 416));
		AddGameObject(wall, eLayerType::CamearaWall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(1072, 224, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(160, 1664));
		AddGameObject(wall, eLayerType::CamearaWall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-16, -416, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(2336, 384));
		AddGameObject(wall, eLayerType::CamearaWall);
	}





#pragma endregion

	{
		GameObjectBuilder::InstantiateGlobalLight2D(this, eLayerType::Default);
	}

	{
		GameObject* player = GameObjectBuilder::InstantiatePlayer(this);
	
		player->GetComponent<Transform>()->SetPosition(0, 0, -30);
	}

	{
		GameObjectBuilder::AddUI(this);
		GameObjectBuilder::AddCamera(this);
	}
}

Chinatown04Scene::~Chinatown04Scene()
{
}
