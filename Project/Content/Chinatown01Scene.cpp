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
	SetBackgroundColor(Vector4(0.f, 0.f, 0.f, 1.f));

	mCollisionManagement2D->TurnOffAllCollisionLayer();

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Bullet);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Default);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Mouse);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Default, eLayerType::Satellite);

	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Mouse, eLayerType::Satellite);


	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Chinatown01_spr_chinatown_parallax_1);
		gResourceManager->Insert(L"Chanatown01Backgorund01", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Chinatown01_spr_chinatown_parallax_2);
		gResourceManager->Insert(L"Chanatown01Backgorund02", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Chinatown01_spr_chinatown_parallax_3);
		gResourceManager->Insert(L"Chanatown01Backgorund03", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::chinatown1_test);
		gResourceManager->Insert(L"ChanatownTest", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Noise_01);
		gResourceManager->Insert(L"Noise01", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Noise_02);
		gResourceManager->Insert(L"Noise02", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Noise_03);
		gResourceManager->Insert(L"Noise03", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::Noise_04);
		gResourceManager->Insert(L"Noise04", material);
	}

	////Map	
	//{
	//	GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"Chanatown01Backgorund01");
	//
	//	obj->GetComponent<Transform>()->SetScale(1.5f, 1.5f, 1.f);
	//	obj->GetComponent<Transform>()->SetPosition(-300.f, 0.f, 35.f);
	//	AddGameObject(obj, eLayerType::Default);
	//}
	//
	//{
	//	GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"Chanatown01Backgorund02");
	//
	//	obj->GetComponent<Transform>()->SetScale(1.5f, 1.5f, 1.f);
	//	obj->GetComponent<Transform>()->SetPosition(-300.f, 0.f, 38.f);
	//	AddGameObject(obj, eLayerType::Default);
	//}
	//
	//{
	//	GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"Chanatown01Backgorund03");
	//
	//	obj->GetComponent<Transform>()->SetScale(1.5f, 1.5f, 1.f);
	//	obj->GetComponent<Transform>()->SetPosition(-300.f, -800.f, 43.f);
	//	AddGameObject(obj, eLayerType::Default);
	//}

	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"ChanatownTest");
		
		obj->GetComponent<Transform>()->SetPosition(800.f, -800.f, 32.f);
		AddGameObject(obj, eLayerType::Default);
	}

	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"Noise01");
		obj->AddComponent<NoiseTest>();

		obj->GetComponent<Transform>()->SetPosition(0.f, 0.f, 32.f);
		
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
		mainCamera->GetComponent<Camera>()->SetProjectionType(eCameraPriorityType::Main);
		mainCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		mainCamera->GetComponent<Camera>()->TurnOnAllLayer();
		mainCamera->GetComponent<Camera>()->TurnOffLayer(eLayerType::UI);

		AddGameObject(mainCamera, eLayerType::Default);
	}

	//UI Camera
	{
		GameObject* const uiCamera = new GameObject();

		uiCamera->AddComponent<Camera>();

		uiCamera->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		uiCamera->GetComponent<Camera>()->SetProjectionType(eCameraPriorityType::UI);
		uiCamera->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		uiCamera->GetComponent<Camera>()->TurnOffAllLayer();
		uiCamera->GetComponent<Camera>()->TurnOnLayer(eLayerType::UI);

		AddGameObject(uiCamera, eLayerType::Default);
	}
}

Chinatown01Scene::~Chinatown01Scene()
{
}
