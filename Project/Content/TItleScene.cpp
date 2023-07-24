#include "pch.h"
#include "TItleScene.h"
#include "Components.h"
#include "ResourceManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include "CameraInputMoveMent.h"
#include "CursorMovement.h"
#include "UIEffect.h"
#include "Bugiman.h"
#include "PlayerMovementTest.h"
#include "ShiftController.h"
#include <Engine/Engine.h>
#include <Engine/SceneManager.h>
#include <Engine/EngineMath.h>
#include "LerpTest.h"
#include <Engine/CollisionManagement2D.h>
#include "InputMovementTest.h"	
#include "ChildTest.h"
#include "ParentTest.h"
#include <Engine/Color.h>
TItleScene::TItleScene()
{

	SetBackgroundColor(helper::Color::BLACK);

	mCollisionManagement2D->TurnOffAllCollisionLayer();

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Bullet);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Default);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Mouse);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Satellite);

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Mouse, eLayerType::Satellite);

	//Title
	
#pragma region Material
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Title_spr_title_background);
		gResourceManager->Insert(L"TitleBackGround", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Title_spr_title_fence);
		gResourceManager->Insert(L"TitleFence", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Title_spr_titlegraphic_big2);
		gResourceManager->Insert(L"TitleGraphic", material);
	}


	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Title_spr_titlegraphic_big_1);
		gResourceManager->Insert(L"TitleGraphic1", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Title_spr_titlegraphic_big_2);
		gResourceManager->Insert(L"TitleGraphic2", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Title_spr_title_grass);
		gResourceManager->Insert(L"TitleGrass", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Title_spr_title_plants_0);
		gResourceManager->Insert(L"TitlePlant", material);
	}

#pragma endregion

#pragma region GameObject

	const Vector2& SCREEN_SIZE = gEngine->GetRenderTargetSize();

	GameObject* const backgroundParent = new GameObject();
	backgroundParent->GetComponent<Transform>()->SetPosition(0.f, 350.f, 0.f);
	backgroundParent->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);
	{
		{
			GameObject* const background = GameObjectBuilder::BuildDefault2DGameObject(L"TitleBackGround");

			background->GetComponent<Transform>()->SetPosition(0.f, 0.f, 32.f);
			background->SetParent(backgroundParent);
			AddGameObject(background, eLayerType::Default);
		}

		{
			GameObject* const fence = GameObjectBuilder::BuildDefault2DGameObject(L"TitleFence");

			fence->GetComponent<Transform>()->SetPosition(0.f, 0.f, 30.f);
			fence->SetParent(backgroundParent);
			AddGameObject(fence, eLayerType::Default);
		}

		{
			GameObject* const grass = GameObjectBuilder::BuildDefault2DGameObject(L"TitleGrass");

			grass->GetComponent<Transform>()->SetPosition(0.f, -320.f, 30.f);
			grass->SetParent(backgroundParent);
			AddGameObject(grass, eLayerType::Default);
		}

		{
			GameObject* const plants = new GameObject();
			plants->GetComponent<Transform>()->SetPosition(0.f, -175.f, 30.f);
			plants->GetComponent<Transform>()->SetScale(1.0f, 1.0f, 1.0f);
			//gResourceManager->LoadByEnum<Texture>(eResTexture::Atlas_Title_Plants);

			Texture* const atlas = gResourceManager->FindByEnum<Texture>(eResTexture::Atlas_Title_Plants);


			plants->AddComponent<Animator2D>();

			Animator2D* const animator = plants->GetComponent< Animator2D>();

			animator->CreateAnimation(L"TitlePlant", atlas, 12, XMUINT2(5, 34),
				XMUINT2(640, 360), XMUINT2(10, 10), XMINT2(0, 0), 0.08f);

			animator->SetMaterial(gResourceManager->FindOrNull<Material>(L"Animator2D"));
			animator->SetMesh(gResourceManager->FindOrNull<Mesh>(L"FillRect2D"));

			animator->SetBackSize(XMUINT2(3000, 3000));
			animator->Play(L"TitlePlant", true);
			
			plants->SetParent(backgroundParent);
			AddGameObject(plants, eLayerType::Default);
		}
	}
	AddGameObject(backgroundParent, eLayerType::Default);



	GameObject* const graphicParent = new GameObject();
	graphicParent->GetComponent<Transform>()->SetScale(1.5f, 1.5f, 1.f);
	graphicParent->GetComponent<Transform>()->SetPosition(0.f, -10.f, 0.f);

	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"TitleGraphic1");

		obj->GetComponent<Transform>()->SetPosition(0.f, 50.f, 31.f);
		obj->SetParent(graphicParent);
		AddGameObject(obj, eLayerType::Default);
	}

	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"TitleGraphic2");

		obj->GetComponent<Transform>()->SetPosition(0.f, 50.f, 31.f);
		obj->SetParent(graphicParent);
		AddGameObject(obj, eLayerType::Default);
	}

	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"TitleGraphic");

		obj->GetComponent<Transform>()->SetPosition(0.f, 100.f, 31.f);
		obj->SetParent(graphicParent);
		AddGameObject(obj, eLayerType::Default);
	}
	AddGameObject(graphicParent, eLayerType::Default);


	//Main Camera
	{
		GameObject* const mainCamera = new GameObject();

		mainCamera->AddComponent<Camera>();
		mainCamera->AddComponent<CameraInputMoveMent>();

		mainCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		mainCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::Main);
		mainCamera->GetComponent<Camera>()->SetRenderTargetSize(SCREEN_SIZE);
		mainCamera->GetComponent<Camera>()->TurnOnAllLayer();
		mainCamera->GetComponent<Camera>()->TurnOffLayer(eLayerType::UI);

		AddGameObject(mainCamera, eLayerType::Default);
	}

	//UI Camera
	{
		GameObject* const uiCamera = new GameObject();

		uiCamera->AddComponent<Camera>();

		uiCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		uiCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::UI);
		uiCamera->GetComponent<Camera>()->SetRenderTargetSize(SCREEN_SIZE);
		uiCamera->GetComponent<Camera>()->TurnOffAllLayer();
		uiCamera->GetComponent<Camera>()->TurnOnLayer(eLayerType::UI);

		AddGameObject(uiCamera, eLayerType::Default);
	}
#pragma endregion

}

TItleScene::~TItleScene()
{

}

