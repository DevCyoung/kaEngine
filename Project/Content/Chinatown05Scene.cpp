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
	: KatanaScene(eKatanaSceneType::ChinaTown05)
{

	
}

Chinatown05Scene::~Chinatown05Scene()
{
}

void Chinatown05Scene::AddMapObject()
{
	{
		GameObject* const backgorund2 = GameObjectBuilder::Default2D(L"Chanatown05BackGround02p");

		//backgorund2->AddComponent<Chinatown04Controller>();

		backgorund2->GetComponent<Transform>()->SetScale(3.6f, 3.6f, 1.f);
		backgorund2->GetComponent<Transform>()->SetPosition(400.f, 150.f, 530.f);

		AddGameObject(backgorund2, eLayerType::BackGround);
	}

	{
		GameObject* const backgorund1 = GameObjectBuilder::Default2D(L"Chanatown05BackGround01p");

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
}

void Chinatown05Scene::AddWallObject()
{
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
}

void Chinatown05Scene::AddDoorObject()
{
}

void Chinatown05Scene::AddMonsterObject()
{
	InstantiateMonster(eMonsterType::Ganster, Vector2(-80, 100), true);	
}

void Chinatown05Scene::AddObject()
{
}

void Chinatown05Scene::AddLightObject()
{
	{
		GameObjectBuilder::InstantiateGlobalLight2D(this, eLayerType::Default);
	}
}

void Chinatown05Scene::AddCameraObject()
{
	GameObject* mainCamera = GameObjectBuilder::AddCamera(this);
	Vector3 pos = mainCamera->GetComponent<Transform>()->GetPosition();
	mainCamera->GetComponent<Transform>()->SetPosition(0, -300, pos.z);

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->AddComponent<CameraWall>();

		wall->GetComponent<Transform>()->SetPosition(1440, 48, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(128, 1504));
		wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Right);

		AddGameObject(wall, eLayerType::CameraWall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->AddComponent<CameraWall>();

		wall->GetComponent<Transform>()->SetPosition(-1008, 32, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(160, 1536));
		wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Left);

		AddGameObject(wall, eLayerType::CameraWall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->AddComponent<CameraWall>();

		wall->GetComponent<Transform>()->SetPosition(192, -704, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(2624, 576));
		wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Down);

		AddGameObject(wall, eLayerType::CameraWall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->AddComponent<CameraWall>();

		wall->GetComponent<Transform>()->SetPosition(192, 600, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(2624, 352));
		wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Up);

		AddGameObject(wall, eLayerType::CameraWall);
	}

}

void Chinatown05Scene::AddUIObject()
{
	GameObjectBuilder::AddUI(this);
}

void Chinatown05Scene::AddPlayerObject()
{
	{
		GameObject* player = GameObjectBuilder::InstantiatePlayer(this);
		player->GetComponent<Transform>()->SetPosition(0, -300, 0);

		GameManager::GetInstance()->SetPlayer(player);
	}

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
}

Scene* Chinatown05Scene::Clone()
{
	return new Chinatown05Scene;
}

KatanaScene* Chinatown05Scene::GetNextScene()
{
	return nullptr;
}
