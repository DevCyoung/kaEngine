#include "pch.h"
#include "Chinatown05Scene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include <Engine/CollisionManagement2D.h>


Chinatown05Scene::Chinatown05Scene()
{
	mCollisionManagement2D->TurnOffAllCollisionLayer();
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Default);

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
	
		AddGameObject(tile, eLayerType::Default);
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

Chinatown05Scene::~Chinatown05Scene()
{
}
