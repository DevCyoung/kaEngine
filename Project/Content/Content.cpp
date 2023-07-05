#include "pch.h"
#include "Content.h"
#include "Components.h"
#include "ResourceManager.h"
#include "StructVertex.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include "CameraInputMoveMent.h"
#include "CursorMovement.h"
#include "UIEffect.h"
#include "Bugiman.h"
#include "ShiftController.h"
#include <Engine/Engine.h>
#include <Engine/SceneManager.h>
#include <Engine/EngineMath.h>

Content::Content()
{
	resourceInitialize();
	testSceneInitialize();
}

Content::~Content()
{
}

void Content::resourceInitialize()
{
	loadMesh();
	loadTexture();
	loadShader();
	loadMaterial();
	loadPrefab();
}

void Content::loadMesh()
{
	{
	

	}
}

void Content::loadTexture()
{
	for (UINT i = 0; i < static_cast<UINT>(eResTexture::End); ++i)
	{
		gResourceManager->LoadByEnum<Texture>(static_cast<eResTexture>(i));
	}
}

void Content::loadShader()
{
	//Default Shader
	{
		Shader* const defaultShader =
			new Shader(eResShader::VSSprite, L"main",
				eResShader::PSSprite, L"main",
				eRSType::CullNone,
				eDSType::Less,
				eBSType::AlphaBlend);
		gResourceManager->Insert(L"Default", defaultShader);
	}


	//UI Shader
	{
		Shader* const UIShader =
			new Shader(eResShader::VSSprite, L"main",
				eResShader::PSSprite, L"main",
				eRSType::CullNone,
				eDSType::None,
				eBSType::AlphaBlend);
		gResourceManager->Insert(L"UIShader", UIShader);
	}


}


void Content::loadMaterial()
{
	loadUIMaterial();

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::door);
		gResourceManager->Insert(L"Default", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::charactor_atlas_zero_black);
		gResourceManager->Insert(L"BlackZero", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::orange);
		gResourceManager->Insert(L"Sample", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::door);
		gResourceManager->Insert(L"Door", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::bg_club_full_0);
		gResourceManager->Insert(L"BackGround01", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::bg_club_full_0);
		gResourceManager->Insert(L"BackGround02", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::bg_dreamshed_0);
		gResourceManager->Insert(L"BackGround03", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::bg_studio_outside_0);
		gResourceManager->Insert(L"BackGround04", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"Default", eResTexture::spr_bg_neighbor_apartment_0);
		gResourceManager->Insert(L"BackGround05", material);
	}
}

void Content::loadUIMaterial()
{
	//Cursor
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"UIShader", eResTexture::UI_spr_cursor);
		gResourceManager->Insert(L"UICursor", material);
	}

	//Hud Bar
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"UIShader", eResTexture::UI_spr_hud);
		gResourceManager->Insert(L"UIHud", material);
	}

	//Hud Timer
	{

		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"UIShader", eResTexture::UI_spr_hud_timer_0);
		gResourceManager->Insert(L"UIHudTimer", material);
	}

	//Timer
	{

		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"UIShader", eResTexture::UI_spr_timer);
		gResourceManager->Insert(L"UITimer", material);
	}

	//Shift 00
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"UIShader", eResTexture::UI_spr_keyboard_shift_0);
		gResourceManager->Insert(L"UIShift00", material);
	}

	//Shift 01
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"UIShader", eResTexture::UI_spr_keyboard_shift_1);
		gResourceManager->Insert(L"UIShift01", material);
	}

	//Battrey
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"UIShader", eResTexture::UI_spr_hud_battery);
		gResourceManager->Insert(L"UIBattery", material);
	}

	//Hud Item
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"UIShader", eResTexture::UI_spr_hud_subweapon);
		gResourceManager->Insert(L"UIHudItem", material);
	}

	//Right Item
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"UIShader", eResTexture::UI_spr_itemicons_0);
		gResourceManager->Insert(L"UIRightItem", material);
	}

	//Left Item
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"UIShader", eResTexture::UI_spr_katanaicons_0);
		gResourceManager->Insert(L"UILeftItem", material);
	}

	//Right Click Mouse
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"UIShader", eResTexture::UI_spr_right_click_1);
		gResourceManager->Insert(L"UIRightClick", material);
	}

	//Left Click Mouse
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderPriorityType::Opqaue, L"UIShader", eResTexture::UI_spr_left_click_1);
		gResourceManager->Insert(L"UILeftClick", material);
	}
}

void Content::loadPrefab()
{
	//GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"Door");
	//Prefab* const prefab = new Prefab(obj);
	//
	//gResourceManager->Insert<Prefab>(L"Door", prefab);
}

void Content::testSceneInitialize()
{
	const Vector2 screenSize = gEngine->GetRenderTargetSize();
	Scene* testScene = new Scene();

	//BackGround parent
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"BlackZero");

		obj->AddComponent<Bugiman>();

		obj->GetComponent<Transform>()->SetScale(2.0f, 2.0f, 1.f);

		testScene->AddGameObject(obj, eLayerType::Default);

		//chid
		{
			GameObject* const child = GameObjectBuilder::BuildDefault2DGameObject(L"BackGround03");

			child->GetComponent<Transform>()->SetPosition(1200.f, 0.f, -100.f);

			child->SetParent(obj);

			testScene->AddGameObject(child, eLayerType::Default);
		}
	}

	//Mouse Cursor
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");

		obj->AddComponent<CursorMovement>();

		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	const float hudPosY = gEngine->GetRenderTargetSize().y / 2.f - 23.f;

	//UI UP Hud
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIHud");

		const Vector2 pos = helper::ScreenToWorldScreen(Vector2(screenSize.x / 2.f, 23.f), screenSize);

		obj->GetComponent<Transform>()->SetPosition(Vector3(pos.x, pos.y, 10.f));
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	constexpr float timerPosX = -8.f;

	//UI HudTimer
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIHudTimer");

		obj->GetComponent<Transform>()->SetPosition(timerPosX, hudPosY + 2.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Timer
	{

		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UITimer");

		obj->AddComponent<UIEffect>();

		obj->GetComponent<Transform>()->SetPosition(timerPosX + 16.f, hudPosY + 6.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UIShift
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIShift00");

		obj->AddComponent<ShiftController>();

		obj->GetComponent<Transform>()->SetPosition(-455.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Battery
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIBattery");

		obj->GetComponent<Transform>()->SetPosition(-561.f, hudPosY - 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Hud Item
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIHudItem");

		obj->GetComponent<Transform>()->SetPosition(+560.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Left Item
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UILeftItem");

		obj->GetComponent<Transform>()->SetPosition(528.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Right Item
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIRightItem");

		obj->GetComponent<Transform>()->SetPosition(592.f, hudPosY + 1.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Left Click
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UILeftClick");

		obj->GetComponent<Transform>()->SetPosition(550.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Right Click
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIRightClick");

		obj->GetComponent<Transform>()->SetPosition(610.f, hudPosY - 24.f, -10.f);
		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//Main Camera
	{
		GameObject* const mainCameraObj = new GameObject();

		mainCameraObj->AddComponent<Camera>();
		mainCameraObj->AddComponent<CameraInputMoveMent>();

		mainCameraObj->GetComponent<Camera>()->SetCameraType(Camera::eCameraPriorityType::Main);
		mainCameraObj->GetComponent<Camera>()->SetRenderTargetRenderer(gEngine->GetRenderTargetRenderer());
		mainCameraObj->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		mainCameraObj->GetComponent<Camera>()->TurnOnAllLayer();
		mainCameraObj->GetComponent<Camera>()->TurnOffLayer(eLayerType::UI);
		mainCameraObj->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);

		testScene->AddGameObject(mainCameraObj, eLayerType::Default);
	}

	//UI Camera
	{
		GameObject* const mainCameraObj = new GameObject();

		mainCameraObj->AddComponent<Camera>();

		mainCameraObj->GetComponent<Camera>()->SetCameraType(Camera::eCameraPriorityType::UI);
		mainCameraObj->GetComponent<Camera>()->SetRenderTargetRenderer(gEngine->GetRenderTargetRenderer());
		mainCameraObj->GetComponent<Camera>()->SetRenderTargetSize(screenSize);
		mainCameraObj->GetComponent<Camera>()->TurnOffAllLayer();
		mainCameraObj->GetComponent<Camera>()->TurnOnLayer(eLayerType::UI);
		mainCameraObj->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);

		testScene->AddGameObject(mainCameraObj, eLayerType::Default);
	}

	SceneManager::GetInstance()->LoadScene(testScene);
}
