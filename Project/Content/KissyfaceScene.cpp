#include "pch.h"
#include "KissyfaceScene.h"
#include "Components.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include <Engine/CollisionManagement2D.h>
#include "SimpleEditorCollider2D.h"
#include "GameManager.h"
#include "PathNode.h"
#include <Engine/Color.h>
#include "GameManager.h"
#include <Engine/SceneManager.h>

KissyfaceScene::KissyfaceScene()
{
	GameManager::initialize();


	mCollisionManagement2D->TurnOffAllCollisionLayer();
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Platform);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Platform);

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Door);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Door);

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Door, eLayerType::PlayerAttack);

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::PlayerAttack);

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Bullet, eLayerType::PlayerAttack);


	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Bullet, eLayerType::PlayerAttack);


	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Camera, eLayerType::CameraWall);


#pragma region Material
	{
		Material* const tileMaterial =
			MaterialBuilder::LightSprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_Kissyface_kissyface_map);
		gResourceManager->Insert(L"KissyfaceMap", tileMaterial);
	}
#pragma endregion

#pragma region Editor
	/*{	
		GameObject* const testObj = new GameObject();
		testObj->AddComponent<SimpleEditorCollider2D>();
		AddGameObject(testObj, eLayerType::Default);
	}*/
#pragma endregion

#pragma region CallObj

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(32, -200, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(1216, 160));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(32, 320, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(1216, 256));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(-528, 64, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(224, 896));
		AddGameObject(wall, eLayerType::Wall);
	}

	{
		GameObject* const wall = new GameObject();
		//[RectCollider]
		wall->AddComponent<RectCollider2D>();
		wall->GetComponent<Transform>()->SetPosition(592, 128, 0);
		wall->GetComponent<RectCollider2D>()->SetSize(Vector2(224, 1024));
		AddGameObject(wall, eLayerType::Wall);
	}

#pragma endregion

#pragma region MapObj
	{
		GameObject* const tile = GameObjectBuilder::Default2D(L"KissyfaceMap");

		tile->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);
		tile->GetComponent<Transform>()->SetPosition(0, 0, 100);
		//tile->AddComponent<Chinatown04Controller>();

		AddGameObject(tile, eLayerType::TileMap);
	}
#pragma endregion

	{
		GameObject* lgiht = GameObjectBuilder::InstantiateGlobalLight2D(this, eLayerType::Default);
		lgiht->GetComponent<Light2D>()->SetLightDiffuse(Vector3::One);
	}


	{
		GameObjectBuilder::AddUI(this);
		GameObjectBuilder::AddCamera(this);
		GameObjectBuilder::InstantiateKissyface(this);
	}

	{
		GameObject* player = GameObjectBuilder::InstantiatePlayer(this);
		player->GetComponent<Transform>()->SetPosition(0, 0, -30);

		GameManager::GetInstance()->SetPlayer(player);
	}

	GameManager::GetInstance()->GetEffectManager()->Initialize(this);
}

KissyfaceScene::~KissyfaceScene()
{
	GameManager::deleteInstance();
}

void KissyfaceScene::lateUpdate()
{
	Scene::lateUpdate();

	GameManager::GetInstance()->GetRewindManager()->LateUpdate();
	//GameManager::GetInstance()->GetEffectManager()->LateUpdate();
}

Scene* KissyfaceScene::Clone()
{
	return nullptr;
}
