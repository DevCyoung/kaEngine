#include "pch.h"
#include "Chinatown05Scene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include "GameManager.h"
#include "SimpleEditorCollider2D.h"
#include "PathNode.h"
#include <Engine/CollisionManagement2D.h>
#include <Engine/Color.h>


Chinatown05Scene::Chinatown05Scene()
{
#pragma region Material
	{
		Material* const backgroundMaterial =
			MaterialBuilder::Sprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown05_spr_chinatown_loop_parallax_1);
		gResourceManager->Insert(L"Chanatown05BackGround01", backgroundMaterial);
	}

	{
		Material* const backgroundMaterial =
			MaterialBuilder::Sprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown05_spr_chinatown_loop_parallax_2);
		gResourceManager->Insert(L"Chanatown05BackGround02", backgroundMaterial);
	}

	{
		Material* const tileMaterial =
			MaterialBuilder::Sprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown05_Tilemap);
		gResourceManager->Insert(L"Chanatown05TileMap", tileMaterial);
	}
#pragma endregion

#pragma region Map
	{
		GameObject* const backgorund2 = GameObjectBuilder::Default2D(L"Chanatown05BackGround02");

		//backgorund2->AddComponent<Chinatown04Controller>();

		backgorund2->GetComponent<Transform>()->SetScale(3.6f, 3.6f, 1.f);
		backgorund2->GetComponent<Transform>()->SetPosition(400.f, 150.f, 530.f);

		AddGameObject(backgorund2, eLayerType::BackGround);
	}

	{
		GameObject* const backgorund1 = GameObjectBuilder::Default2D(L"Chanatown05BackGround01");

		//backgorund1->AddComponent<Chinatown04Controller>();

		backgorund1->GetComponent<Transform>()->SetScale(2.8f, 2.8f, 1.f);
		backgorund1->GetComponent<Transform>()->SetPosition(400.f, 150.f, 480.f);

		AddGameObject(backgorund1, eLayerType::BackGround);
	}

	{
		GameObject* const tile = GameObjectBuilder::Default2D(L"Chanatown05TileMap");
		//tile->AddComponent<Chinatown04Controller>();

		AddGameObject(tile, eLayerType::TileMap);
	}

#pragma endregion

#pragma region Editor
	/*{
		GameObject* const testObj = new GameObject();
		testObj->AddComponent<SimpleEditorCollider2D>();
		AddGameObject(testObj, eLayerType::Default);
	}*/
#pragma endregion

#pragma region Map
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-496, -272, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(672, 160));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(672, -384, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(1408, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-160, -192, -32, -320);
		AddGameObject(wall, eLayerType::LeftSlope);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-896, 96, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(128, 768));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-672, 320, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(704, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-288, 336, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 288));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-288, 0, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 128));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(384, -64, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 256));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(48, 544, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(608, 256));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(384, 480, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(64, 576));
		AddGameObject(wall, eLayerType::Wall);
	}



	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-832, 64, -320, 64);
		AddGameObject(wall, eLayerType::Platform);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-256, 64, 352, 64);
		AddGameObject(wall, eLayerType::Platform);
	}

	{
		GameObject* const wall = new GameObject();
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(416, 64, 512, 64);
		AddGameObject(wall, eLayerType::Platform);
	}


#pragma endregion

#pragma region PathNode
	PathInfo* const pathInfo = GameManager::GetInstance()->GetPathInfo();
	

	{
		GameObject* const wall = new GameObject();

		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());
		
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-832, -192, -480, -192);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::BLUE);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();

		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());
		
		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-480, -192, -480, -96);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::WHITE);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Elevator);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-480, -192, -160, -192);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-160, -192, -32, -320);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::YELLOW);
		wall->GetComponent<PathNode>()->SetType(eLayerType::LeftSlope);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-32, -320, 1376, -320);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

		AddGameObject(wall, eLayerType::PathNode);
	}


	//2Ãþ
	{
		GameObject* const wall = new GameObject();
		
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-832, 64, -480, 64);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::MAGENTA);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-480, 64, -480, 160);

		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::WHITE);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Elevator);

		AddGameObject(wall, eLayerType::PathNode);
	}

	{
		GameObject* const wall = new GameObject();
		
		//[LineCollider]
		wall->AddComponent<LineCollider2D>();
		wall->AddComponent<PathNode>();

		pathInfo->AddPathNode(wall->GetComponent<PathNode>());

		wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		wall->GetComponent<LineCollider2D>()->SetPoints(-480, 64, 512, 64);
		
		wall->GetComponent<LineCollider2D>()->TurnOnVisible();
		wall->GetComponent<LineCollider2D>()->SetColor(helper::Color::BLUE);
		wall->GetComponent<PathNode>()->SetType(eLayerType::Wall);

		AddGameObject(wall, eLayerType::PathNode);
	}


	//0
	pathInfo->InsertEdge(0, 1, 1);

	//1 elevator
	pathInfo->InsertEdge(1, 0, 1);
	pathInfo->InsertEdge(1, 2, 1);
	pathInfo->InsertEdge(1, 6, 1);

	//2
	pathInfo->InsertEdge(2, 1, 1);
	pathInfo->InsertEdge(2, 3, 1);

	//3
	pathInfo->InsertEdge(3, 2, 1);
	pathInfo->InsertEdge(3, 4, 1);

	//4
	pathInfo->InsertEdge(4, 3, 1);

	//5
	pathInfo->InsertEdge(5, 6, 1);

	//6 elevator
	pathInfo->InsertEdge(6, 5, 1);
	pathInfo->InsertEdge(6, 7, 1);
	pathInfo->InsertEdge(6, 1, 1);

	//7
	pathInfo->InsertEdge(7, 6, 1);


#pragma endregion

#pragma region Monster
	{
		GameObject* monster = GameObjectBuilder::InstantiateMonster(eMonsterType::Ganster, this);
		monster->GetComponent<Transform>()->SetPosition(-80, 150, -30);
	}

#pragma endregion



#pragma region Global
	{
		GameObject* player = GameObjectBuilder::InstantiatePlayer(this);
		player->GetComponent<Transform>()->SetPosition(0, 0, -30);

		//player->GetComponent<Rigidbody2D>()->TurnOffGravity();

		GameManager::GetInstance()->SetPlayer(player);
	}

	{
		GameObject* lgiht = GameObjectBuilder::InstantiateGlobalLight2D(this, eLayerType::Default);
		lgiht->GetComponent<Light2D>()->SetLightDiffuse(Vector3::One);
	}

	{
		GameObjectBuilder::AddUI(this);
		GameObjectBuilder::AddCamera(this);
	}
#pragma endregion


}

Chinatown05Scene::~Chinatown05Scene()
{
}
