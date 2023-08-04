#include "pch.h"
#include "HeadHunterScene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include <Engine/CollisionManagement2D.h>

#include <Engine/Light2D.h>
#include "InputMovementTest.h"

#include "PlayerController.h"

HeadHunterScene::HeadHunterScene()
{
	mCollisionManagement2D->TurnOffAllCollisionLayer();

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::LeftSlope);

	{
		Material* const material =
			MaterialBuilder::LightSprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_HeadHunter_map);
		gResourceManager->Insert(L"HeadHunterMap", material);
	}

	{
		Material* const material =
			MaterialBuilder::LightSprite2D(
				eRenderPriorityType::Opqaue, eResTexture::Map_HeadHunter_spr_vaultdoor_open_spr_vaultdoor_open_0);

		gResourceManager->Insert(L"HeadHunterMapDoor", material);
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
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();


		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::DIRECTIONAL);
		light->GetComponent<Light2D>()->SetRadius(300.f);
		//light->GetComponent<Light2D>()->SetLightAmbient(Vector3(1.f, 0.f, 0.f));
		light->GetComponent<Light2D>()->SetLightDiffuse(Vector3(1.f, 1.f, 1.f));

		light->GetComponent<Transform>()->SetPosition(100, 0.f, 0.f);

		AddGameObject(light, eLayerType::Default);
	}

	{
		GameObject* const player = GameObjectBuilder::Player();

		//player->GetComponent<Rigidbody2D>()->SetGravityAccel();

		player->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		player->GetComponent<Animator2D>()->GetMaterial()->SetShader(
			gResourceManager->FindOrNull<Shader>(L"LightAnimation2D"));

		AddGameObject(player, eLayerType::Player);

		{
			GameObject* const Slash = new GameObject();

			Slash->AddComponent<Animator2D>();
			Slash->AddComponent<CircleCollider2D>();

			Slash->GetComponent<CircleCollider2D>()->SetRadius(50.f);

			Animator2D* const animator = Slash->GetComponent<Animator2D>();

			animator->GetMaterial()->SetShader(
				gResourceManager->FindOrNull<Shader>(L"LightAnimation2D"));

			Texture* atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Player_slash);

			animator->CreateAnimation(L"Slash", atlas, 6, XMUINT2(5, 34), XMUINT2(106, 32), XMUINT2(10, 10), XMINT2(0, 0), 0.04f);

			Slash->SetParent(player);

			player->GetComponent<PlayerController>()->SetSlash(Slash);

			Slash->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);

			AddGameObject(Slash, eLayerType::Default);
		}
	}

	//Wall
	{
		GameObject* const obj = new GameObject();

		obj->AddComponent<RectCollider2D>();

		obj->GetComponent<RectCollider2D>()->SetSize(800.f, 50.f);
		obj->GetComponent<Transform>()->SetPosition(0.f, -300.f, 1.f);

		AddGameObject(obj, eLayerType::Wall);
	}

	{
		GameObject* const obj = new GameObject();

		obj->AddComponent<RectCollider2D>();

		obj->GetComponent<RectCollider2D>()->SetSize(700.f, 50.f);
		obj->GetComponent<Transform>()->SetPosition(-450.f, -50.f, 1.f);
		obj->GetComponent<Transform>()->SetRotation(0.f, 0.f, -45.f);

		AddGameObject(obj, eLayerType::LeftSlope);
	}

	{
		GameObject* const obj = new GameObject();

		obj->AddComponent<RectCollider2D>();

		obj->GetComponent<RectCollider2D>()->SetSize(700.f, 50.f);
		obj->GetComponent<Transform>()->SetPosition(-1605.f, -50.f, 1.f);
		obj->GetComponent<Transform>()->SetRotation(0.f, 0.f, 45.f);

		AddGameObject(obj, eLayerType::LeftSlope);
	}

	{
		GameObject* const obj = new GameObject();

		obj->AddComponent<RectCollider2D>();

		obj->GetComponent<RectCollider2D>()->SetSize(700.f, 50.f);
		obj->GetComponent<Transform>()->SetPosition(-1030.f, 190.f, 1.f);
		obj->GetComponent<Transform>()->SetRotation(0.f, 0.f, 0.f);

		AddGameObject(obj, eLayerType::Wall);
	}


	{
		GameObject* const obj = new GameObject();

		obj->AddComponent<RectCollider2D>();

		obj->GetComponent<RectCollider2D>()->SetSize(50.f, 700.f);
		obj->GetComponent<Transform>()->SetPosition(350.f, 0.f, 1.f);

		AddGameObject(obj, eLayerType::Wall);
	}


	{
		GameObject* const obj = new GameObject();

		obj->AddComponent<RectCollider2D>();

		obj->GetComponent<RectCollider2D>()->SetSize(50.f, 700.f);
		obj->GetComponent<Transform>()->SetPosition(100.f, 200.f, 1.f);

		AddGameObject(obj, eLayerType::Wall);
	}

	{
		GameObjectBuilder::AddUI(this);
		GameObjectBuilder::AddCamera(this);
	}
}

HeadHunterScene::~HeadHunterScene()
{
}
