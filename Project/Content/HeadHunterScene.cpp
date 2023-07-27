#include "pch.h"
#include "HeadHunterScene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include <Engine/CollisionManagement2D.h>

#include <Engine/Light2D.h>
#include "InputMovementTest.h"

HeadHunterScene::HeadHunterScene()
{
	mCollisionManagement2D->TurnOffAllCollisionLayer();
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Default);

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

	//{
	//	GameObject* const light = new GameObject();		
	//	light->AddComponent<Light2D>();
	//	light->AddComponent<InputMovementTest>();
	//	
	//	
	//	light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
	//	light->GetComponent<Light2D>()->SetRadius(300.f);		
	//	light->GetComponent<Light2D>()->SetLightAmbient(Vector3(1.f, 1.f, 1.f));
	//	light->GetComponent<Light2D>()->SetLightDiffuse(Vector3(1.f, 1.f, 1.f));
	//
	//	light->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);
	//	light->GetComponent<Transform>()->SetPosition(0, 0.f, 0.f);
	//
	//
	//	AddGameObject(light, eLayerType::Default);
	//}


	//{
	//	GameObject* const light = new GameObject();
	//	light->AddComponent<Light2D>();		
	//
	//
	//	light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
	//	light->GetComponent<Light2D>()->SetRadius(300.f);
	//	light->GetComponent<Light2D>()->SetLightAmbient(Vector3(1.f, 1.f, 1.f));
	//	light->GetComponent<Light2D>()->SetLightDiffuse(Vector3(1.f, 1.f, 1.f));
	//	
	//	light->GetComponent<Transform>()->SetPosition(-300, 0.f, 0.f);
	//
	//	AddGameObject(light, eLayerType::Default);
	//}

	
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

	//{
	//	GameObject* const light = new GameObject();
	//	light->AddComponent<Light2D>();
	//
	//
	//	light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
	//	light->GetComponent<Light2D>()->SetRadius(300.f);
	//	//light->GetComponent<Light2D>()->SetLightAmbient(Vector3(1.f, 1.f, 1.f));
	//	light->GetComponent<Light2D>()->SetLightDiffuse(Vector3(0.f, 1.f, 0.f));
	//
	//	light->GetComponent<Transform>()->SetPosition(100, 0.f, 0.f);
	//
	//	AddGameObject(light, eLayerType::Default);
	//}
	//
	//{
	//	GameObject* const light = new GameObject();
	//	light->AddComponent<Light2D>();
	//
	//
	//	light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
	//	light->GetComponent<Light2D>()->SetRadius(300.f);
	//	//light->GetComponent<Light2D>()->SetLightAmbient(Vector3(1.f, 1.f, 1.f));
	//	light->GetComponent<Light2D>()->SetLightDiffuse(Vector3(0.f, 0.f, 1.f));
	//
	//	light->GetComponent<Transform>()->SetPosition(-100.f, 0.f, 0.f);
	//
	//	AddGameObject(light, eLayerType::Default);
	//}
	//
	//

	{
		GameObject* const light = new GameObject();
		light->AddComponent<Light2D>();
		light->AddComponent<InputMovementTest>();
	
		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::SPOT);
		light->GetComponent<Light2D>()->SetRadius(300.f);
		light->GetComponent<Light2D>()->SetAngle(80.f);
		//light->GetComponent<Light2D>()->SetLightAmbient(Vector3(1.f, 1.f, 1.f));
		light->GetComponent<Light2D>()->SetLightDiffuse(Vector3(5.f, 5.f, 5.f));
	
		light->GetComponent<Transform>()->SetPosition(-100.f, 0.f, 0.f);
		light->GetComponent<Transform>()->SetRotation(0.f, 0.f, -90.f);
	
		AddGameObject(light, eLayerType::Default);
	}


	//for (int i = 0; i < 100; ++i)
	//{
	//	{
	//		GameObject* const light = new GameObject();
	//		light->AddComponent<Light2D>();
	//
	//		light->AddComponent<InputMovementTest>();
	//
	//
	//		light->GetComponent<Light2D>()->SetLightType(Light2D::LIGHT_TYPE::POINT);
	//		light->GetComponent<Light2D>()->SetRadius(150.f);
	//		//light->GetComponent<Light2D>()->SetLightAmbient(Vector3(1.f, 1.f, 1.f));
	//		light->GetComponent<Light2D>()->SetLightDiffuse(Vector3(1.f, 1.f, 1.f));
	//		//light->GetComponent<Light2D>()->SetLightAmbient(Vector3(0.f, 1.f, 1.f) * 10.f);	
	//
	//		int len = 500;
	//		float angle = (360.f / 100.f) * i;
	//		Vector3 pos = Vector3(cosf(angle) * len, sinf(angle) * len, 0.f);			
	//		light->GetComponent<Transform>()->SetPosition(pos);
	//		AddGameObject(light, eLayerType::Default);
	//	}
	//}	

	{
		GameObject* const player = GameObjectBuilder::Player();
	
		player->GetComponent<Rigidbody2D>()->TurnOffGravity();

		player->GetComponent<Animator2D>()->GetMaterial()->SetShader(
			gResourceManager->FindOrNull<Shader>(L"LightAnimation2D"));
	
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
