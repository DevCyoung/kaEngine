#include "pch.h"
#include "HeadHunterScene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include <Engine/CollisionManagement2D.h>

#include <Engine/Light2D.h>
#include "InputMovementTest.h"
#include "FolowPlayer.h"
#include "PlayerController.h"

HeadHunterScene::HeadHunterScene()
	: KatanaScene(eKatanaSceneType::HeadHunter)
{
	SetBackgroundColor(Vector4(0.f, 0.f, 0.f, 1.f));
}

HeadHunterScene::~HeadHunterScene()
{
}

void HeadHunterScene::AddMapObject()
{
	{
		GameObject* const tile = GameObjectBuilder::Default2D(L"HeadHunterMap");		
		tile->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
		AddGameObject(tile, eLayerType::TileMap);
	}

	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"HeadHunterMapDoor");
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
		obj->GetComponent<Transform>()->SetPosition(18.f, -182.f, 0.f);
		AddGameObject(obj, eLayerType::TileMap);
	}
}

void HeadHunterScene::AddWallObject()
{
	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(0, -312, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(1024, 96));
		AddGameObject(wall, eLayerType::Wall);
	}

	//{
	//	GameObject* const wall = new GameObject();
	//	//[RectCollider]
	//	wall->AddComponent<RectCollider2D>();
	//	wall->GetComponent<Transform>()->SetPosition(0, 176, 0);
	//	wall->GetComponent<RectCollider2D>()->SetSize(Vector2(1024, 96));
	//	AddGameObject(wall, eLayerType::Wall);
	//}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-576, -64, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(128, 576));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(576, -64, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(128, 576));
		AddGameObject(wall, eLayerType::Wall);
	}

}

void HeadHunterScene::AddDoorObject()
{
}

void HeadHunterScene::AddMonsterObject()
{
	GameObjectBuilder::InstantiateHeadHunter(this);
}

void HeadHunterScene::AddObject()
{
}

void HeadHunterScene::AddLightObject()
{
	GameObjectBuilder::InstantiateGlobalLight2D(this, eLayerType::Default);	
}

void HeadHunterScene::AddCameraObject()
{
	{
		GameObject* mainCamera = GameObjectBuilder::AddCamera(this);
		Vector3 pos = mainCamera->GetComponent<Transform>()->GetPosition();

		mainCamera->GetComponent<Transform>()->SetPosition(0, -70, pos.z);
		mainCamera->GetComponent<FolowPlayer>()->SetFolow(false);
	}
}

void HeadHunterScene::AddUIObject()
{
#pragma region UI
	GameObjectBuilder::AddUI(this);
#pragma endregion
}

void HeadHunterScene::AddPlayerObject()
{
	{
		GameObject* player = GameObjectBuilder::InstantiatePlayer(this);
		player->GetComponent<Transform>()->SetPosition(0, -250, 0);

		GameManager::GetInstance()->SetPlayer(player);
	}
}

Scene* HeadHunterScene::Clone()
{
	return new HeadHunterScene;
}

KatanaScene* HeadHunterScene::GetNextScene()
{
	return nullptr;
}
