#include "pch.h"
#include "Chinatown04Scene.h"
#include "Components.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include <Engine/CollisionManagement2D.h>

Chinatown04Scene::Chinatown04Scene()
{
	mCollisionManagement2D->TurnOffAllCollisionLayer();
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Default);

	{
		Material* const tileMaterial =
			MaterialBuilder::Sprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown04_Tilemap);
		gResourceManager->Insert(L"Chanatown04TileMap", tileMaterial);
	}

	{
		GameObject* const tile = GameObjectBuilder::Default2D(L"Chanatown04TileMap");
		//tile->AddComponent<Chinatown04Controller>();

		AddGameObject(tile, eLayerType::Default);
	}

	{
		GameObject* const obj = new GameObject();

		obj->GetComponent<Transform>()->SetPosition(500.f, 400.f, 1.f);

		obj->AddComponent<CircleCollider2D>();

		AddGameObject(obj, eLayerType::Default);
	}

	{
		GameObject* const obj = new GameObject();

		obj->AddComponent<RectCollider2D>();
		//obj->AddComponent<InputMovementTest>();

		obj->GetComponent<Transform>()->SetPosition(150.f, 0.f, 1.f);

		AddGameObject(obj, eLayerType::Player);
	}


	{
		GameObject* const player = GameObjectBuilder::Player();

		player->GetComponent<Rigidbody2D>()->TurnOffGravity();

		AddGameObject(player, eLayerType::Default);
	}

	{
		GameObjectBuilder::AddUI(this);
		GameObjectBuilder::AddCamera(this);
	}
}

Chinatown04Scene::~Chinatown04Scene()
{
}
