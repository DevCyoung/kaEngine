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
	{
		GameObject* const tile = GameObjectBuilder::Default2D(L"BlackOut");
		tile->SetName(L"WhiteUI");
		tile->GetComponent<SpriteRenderer>()->TurnOffVisiblelity();

		tile->GetComponent<Transform>()->SetScale(20.f, 20.f, 1.f);		
		tile->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);

		tile->GetComponent<SpriteRenderer>()->SetColorA(1.0f);
		AddGameObject(tile, eLayerType::Forground);
	}

	{
		GameObject* const tile = GameObjectBuilder::Default2D(L"BlackOut");
		tile->SetName(L"BlackUI");
		tile->GetComponent<SpriteRenderer>()->TurnOffVisiblelity();

		tile->GetComponent<Transform>()->SetScale(10.2f, 10.f, 1.f);		
		tile->GetComponent<Transform>()->SetPosition(0.f, 236.f, 0.f);

		AddGameObject(tile, eLayerType::Forground);
	}
}

void HeadHunterScene::AddLightObject()
{
	GameObjectBuilder::InstantiateGlobalLight2D(this, eLayerType::Default);	


	Vector3 difuse = Vector3(0.1f, 1.35f, 1.35f) * 1.4f;
	//float radius = 120.f;
	float radius = 240.f;

	{
		GameObject* const light = new GameObject();
		light->SetName(L"DefuseLight");

		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(0, 100, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->SetName(L"DefuseLight");

		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(-300, 100, 0);
		AddGameObject(light, eLayerType::Light);
	}

	{
		GameObject* const light = new GameObject();
		light->SetName(L"DefuseLight");

		light->AddComponent<Light2D>();

		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
		light->GetComponent<Light2D>()->SetRadius(radius);
		light->GetComponent<Light2D>()->SetLightDiffuse(difuse);
		light->GetComponent<Transform>()->SetPosition(300, 100, 0);
		AddGameObject(light, eLayerType::Light);
	}
}

void HeadHunterScene::AddCameraObject()
{
	{
		GameObject* mainCamera = GameObjectBuilder::AddCamera(this);
		Vector3 pos = mainCamera->GetComponent<Transform>()->GetPosition();

		mainCamera->GetComponent<Transform>()->SetPosition(0, -70, pos.z);
		mainCamera->GetComponent<FolowPlayer>()->SetFolow(false);
	}

	//{
	//	GameObject* const wall = new GameObject();
	//	//[RectCollider]
	//	wall->AddComponent<RectCollider2D>();
	//	wall->AddComponent<CameraWall>();

	//	wall->GetComponent<Transform>()->SetPosition(-736, -96, 0);
	//	wall->GetComponent<RectCollider2D>()->SetSize(Vector2(192, 896));

	//	wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Left);
	//	AddGameObject(wall, eLayerType::CameraWall);
	//}

	//{
	//	GameObject* const wall = new GameObject();
	//	//[RectCollider]
	//	wall->AddComponent<RectCollider2D>();
	//	wall->AddComponent<CameraWall>();

	//	wall->GetComponent<Transform>()->SetPosition(-32, -480, 0);
	//	wall->GetComponent<RectCollider2D>()->SetSize(Vector2(1600, 128));

	//	wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Down);
	//	AddGameObject(wall, eLayerType::CameraWall);
	//}

	//{
	//	GameObject* const wall = new GameObject();
	//	//[RectCollider]
	//	wall->AddComponent<RectCollider2D>();
	//	wall->AddComponent<CameraWall>();

	//	wall->GetComponent<Transform>()->SetPosition(720, -80, 0);
	//	wall->GetComponent<RectCollider2D>()->SetSize(Vector2(160, 928));

	//	wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Right);
	//	AddGameObject(wall, eLayerType::CameraWall);
	//}

	//{
	//	GameObject* const wall = new GameObject();
	//	//[RectCollider]
	//	wall->AddComponent<RectCollider2D>();
	//	wall->AddComponent<CameraWall>();

	//	wall->GetComponent<Transform>()->SetPosition(-16, 352, 0);
	//	wall->GetComponent<RectCollider2D>()->SetSize(Vector2(1632, 128));
	//	
	//	wall->GetComponent<CameraWall>()->SetCameraWallType(eCameraWallType::Up);
	//	AddGameObject(wall, eLayerType::CameraWall);
	//}

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
		player->GetComponent<Transform>()->SetPosition(-300, -250, 0);

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
