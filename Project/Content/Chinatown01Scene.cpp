#include "pch.h"
#include "Chinatown01Scene.h"
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
#include "NoiseTest.h"

Chinatown01Scene::Chinatown01Scene()
{
	SetBackgroundColor(Vector4(0.5294f, 0.5254f, 0.7843f, 1.f));

	mCollisionManagement2D->TurnOffAllCollisionLayer();

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Default);

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Map_Chinatown01_spr_chinatown_parallax_1);
		gResourceManager->Insert(L"Chanatown05BackGround01", material);
	}
	
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Map_Chinatown01_spr_chinatown_parallax_2);
		gResourceManager->Insert(L"Chanatown05BackGround02", material);
	}


	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Map_Chinatown01_spr_chinatown_parallax_3);
		gResourceManager->Insert(L"Chanatown05BackGround03", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Map_Chinatown01_Tilemap);
		gResourceManager->Insert(L"Chanatown01TileMap", material);
	}

	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"Chanatown05BackGround01");
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);
		obj->GetComponent<Transform>()->SetPosition(-580, 560.f, 500.f);

		AddGameObject(obj, eLayerType::BackGround);
	}

	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"Chanatown05BackGround02");

		obj->GetComponent<Transform>()->SetScale(2.5f, 2.5f, 1.f);
		obj->GetComponent<Transform>()->SetPosition(-640, 560.f, 600.f);

	
		AddGameObject(obj, eLayerType::BackGround);
	}

	
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"Chanatown05BackGround03");

		obj->GetComponent<Transform>()->SetScale(2.5f, 2.5f, 1.f);
		obj->GetComponent<Transform>()->SetPosition(-640, 560.f, 700.f);
	
		AddGameObject(obj, eLayerType::BackGround);
	}


	//Map
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"Chanatown01TileMap");		

		AddGameObject(obj, eLayerType::Default);
	}

#pragma region UIGameOBject
	//UI
	const Vector2 screenSize = gEngine->GetRenderTargetSize();
	const float hudPosY = gEngine->GetRenderTargetSize().y / 2.f - 23.f;

	//UI UP Hud
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIHud");

		const Vector2 pos = helper::RenderTargetToWorldUI(Vector2(screenSize.x / 2.f, 23.f), screenSize);

		obj->GetComponent<Transform>()->SetPosition(Vector3(pos.x, pos.y, 10.f));
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		AddGameObject(obj, eLayerType::UI);
	}

	constexpr float timerPosX = -8.f;

	//UI HudTimer
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIHudTimer");

		obj->GetComponent<Transform>()->SetPosition(timerPosX, hudPosY + 2.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		AddGameObject(obj, eLayerType::UI);
	}

	//UI Timer
	{

		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UITimer");

		obj->AddComponent<UIEffect>();

		obj->GetComponent<Transform>()->SetPosition(timerPosX + 16.f, hudPosY + 6.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		AddGameObject(obj, eLayerType::UI);
	}

	//UIShift
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIShift00");

		obj->AddComponent<ShiftController>();

		obj->GetComponent<Transform>()->SetPosition(-455.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		AddGameObject(obj, eLayerType::UI);
	}

	//UI Battery
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIBattery");

		obj->GetComponent<Transform>()->SetPosition(-561.f, hudPosY - 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		AddGameObject(obj, eLayerType::UI);

		for (UINT i = 0; i < 11; ++i)
		{
			//UI BatteryPart
			{
				GameObject* const part = GameObjectBuilder::BuildDefault2DGameObject(L"UIBatteryPart");

				part->GetComponent<Transform>()->SetPosition(-25.5f + i * 5.f, 0.5f, 0.f);
				part->SetParent(obj);
				AddGameObject(part, eLayerType::UI);
			}
		}

	}

	//UI Hud Item
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIHudItem");

		obj->GetComponent<Transform>()->SetPosition(+560.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		AddGameObject(obj, eLayerType::UI);
	}

	//UI Left Item
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UILeftItem");

		obj->GetComponent<Transform>()->SetPosition(528.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		AddGameObject(obj, eLayerType::UI);
	}

	//UI Right Item
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIRightItem");

		obj->GetComponent<Transform>()->SetPosition(592.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		AddGameObject(obj, eLayerType::UI);
	}

	//UI Left Click
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UILeftClick");

		obj->GetComponent<Transform>()->SetPosition(550.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		AddGameObject(obj, eLayerType::UI);
	}

	//UI Right Click
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIRightClick");

		obj->GetComponent<Transform>()->SetPosition(610.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		AddGameObject(obj, eLayerType::UI);
	}

#pragma endregion



	//Main Camera
	{
		GameObject* const mainCamera = new GameObject();

		mainCamera->AddComponent<Camera>();
		mainCamera->AddComponent<CameraInputMoveMent>();

		mainCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		mainCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::Main);
		mainCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		mainCamera->GetComponent<Camera>()->TurnOnAllLayer();
		mainCamera->GetComponent<Camera>()->TurnOffLayer(eLayerType::UI);
		mainCamera->GetComponent<Camera>()->TurnOffLayer(eLayerType::BackGround);

		AddGameObject(mainCamera, eLayerType::Default);

		//backGorund Camera
		{
			GameObject* const backgroundCamera = new GameObject();

			backgroundCamera->AddComponent<Camera>();
			//backgroundCamera->AddComponent<CameraInputMoveMent>();

			backgroundCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -110.f);
			backgroundCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::BackGround);
			backgroundCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
			backgroundCamera->GetComponent<Camera>()->SetProjectionType(eCameraProjectionType::Perspective);

			backgroundCamera->GetComponent<Camera>()->TurnOffAllLayer();
			backgroundCamera->GetComponent<Camera>()->TurnOnLayer(eLayerType::BackGround);

			backgroundCamera->SetParent(mainCamera);
			AddGameObject(backgroundCamera, eLayerType::Default);
		}
	}

	//UI Camera
	{
		GameObject* const uiCamera = new GameObject();

		uiCamera->AddComponent<Camera>();

		uiCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		uiCamera->GetComponent<Camera>()->SetPriorityType(eCameraPriorityType::UI);
		uiCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		uiCamera->GetComponent<Camera>()->TurnOffAllLayer();
		uiCamera->GetComponent<Camera>()->TurnOnLayer(eLayerType::UI);

		AddGameObject(uiCamera, eLayerType::Default);
	}
}

Chinatown01Scene::~Chinatown01Scene()
{
}
