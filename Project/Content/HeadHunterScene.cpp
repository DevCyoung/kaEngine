#include "pch.h"
#include "HeadHunterScene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include <Engine/CollisionManagement2D.h>
HeadHunterScene::HeadHunterScene()
{
	mCollisionManagement2D->TurnOffAllCollisionLayer();
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Default);

	{
		Material* const material =
			MaterialBuilder::Sprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_HeadHunter_map);
		gResourceManager->Insert(L"HeadHunterMap", material);
	}

	{
		Material* const material =
			MaterialBuilder::Sprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_HeadHunter_spr_vaultdoor_open_spr_vaultdoor_open_0);

		gResourceManager->Insert(L"HeadHunterMapDoor", material);
	}

	{
		Material* const material =
			MaterialBuilder::Sprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_Chinatown05_Tilemap);
		gResourceManager->Insert(L"Chanatown05TileMap", material);
	}

	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"HeadHunterMap");
	
		obj->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);		
	
		AddGameObject(obj, eLayerType::Default);
	}
	
	{
		GameObject* const obj = GameObjectBuilder::Default2D(L"HeadHunterMapDoor");
	
		obj->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);
		obj->GetComponent<Transform>()->SetPosition(18.f, -182.f, 0.f);
	
		AddGameObject(obj, eLayerType::Default);
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

HeadHunterScene::~HeadHunterScene()
{
}
