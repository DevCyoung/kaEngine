#include "pch.h"
#include "Content.h"
#include <Engine/Engine.h>
#include <Engine/SceneManager.h>
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
}

void Content::loadMesh()
{
	{
		//RectMesh
		const UINT VERTEX_COUNT = 4;
		tVertex vertexs[VERTEX_COUNT] = {};
		//0---1
		//|   |
		//3---2
		vertexs[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexs[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexs[0].uv = Vector2(0.0f, 0.0f);

		vertexs[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexs[1].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexs[1].uv = Vector2(1.0f, 0.0f);

		vertexs[2].pos = Vector3(+0.5f, -0.5f, 0.0f);
		vertexs[2].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexs[2].uv = Vector2(1.0f, 1.0f);

		vertexs[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexs[3].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexs[3].uv = Vector2(0.0f, 1.0f);

		std::vector<UINT> indexes;
		indexes.reserve(10);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		gResourceManager->Insert<Mesh>(L"Rect",
			new Mesh(vertexs, VERTEX_COUNT, sizeof(tVertex),
				indexes.data(), indexes.size(), sizeof(UINT)));
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
			new Shader(eResShader::VertexShader, L"main",
				eResShader::PixelShader, L"main",
				eRSType::CullNone,
				eDSType::Less,
				eBSType::AlphaBlend);
		gResourceManager->Insert<Shader>(L"Default", defaultShader);
	}

	//UI Shader
	{
		Shader* const UIShader =
			new Shader(eResShader::VertexShader, L"main",
				eResShader::PixelShader, L"main",
				eRSType::CullNone,
				eDSType::None,
				eBSType::AlphaBlend);
		gResourceManager->Insert<Shader>(L"UIShader", UIShader);
	}
}


void Content::loadMaterial()
{
	loadUIMaterial();

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"Default", eResTexture::door);
		gResourceManager->Insert<Material>(L"Default", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"Default", eResTexture::orange);
		gResourceManager->Insert<Material>(L"Sample", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"Default", eResTexture::bg_club_full_0);
		gResourceManager->Insert<Material>(L"BackGround01", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"Default", eResTexture::door);
		gResourceManager->Insert<Material>(L"Door", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"Default", eResTexture::bg_club_full_0);
		gResourceManager->Insert<Material>(L"BackGround02", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"Default", eResTexture::bg_dreamshed_0);
		gResourceManager->Insert<Material>(L"BackGround03", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"Default", eResTexture::bg_studio_outside_0);
		gResourceManager->Insert<Material>(L"BackGround04", material);
	}

	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"Default", eResTexture::spr_bg_neighbor_apartment_0);
		gResourceManager->Insert<Material>(L"BackGround05", material);
	}
}

void Content::loadUIMaterial()
{
	//Cursor
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"UIShader", eResTexture::UI_spr_cursor);
		gResourceManager->Insert<Material>(L"UICursor", material);
	}

	//Hud Bar
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"UIShader", eResTexture::UI_spr_hud);
		gResourceManager->Insert<Material>(L"UIHud", material);
	}

	//Hud Timer
	{

		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"UIShader", eResTexture::UI_spr_hud_timer_0);
		gResourceManager->Insert<Material>(L"UIHudTimer", material);
	}

	//Timer
	{

		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"UIShader", eResTexture::UI_spr_timer);
		gResourceManager->Insert<Material>(L"UITimer", material);
	}

	//Shift 00
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"UIShader", eResTexture::UI_spr_keyboard_shift_0);
		gResourceManager->Insert<Material>(L"UIShift00", material);
	}

	//Shift 01
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"UIShader", eResTexture::UI_spr_keyboard_shift_1);
		gResourceManager->Insert<Material>(L"UIShift01", material);
	}

	//Battrey
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"UIShader", eResTexture::UI_spr_hud_battery);
		gResourceManager->Insert<Material>(L"UIBattery", material);
	}

	//Hud Item
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"UIShader", eResTexture::UI_spr_hud_subweapon);
		gResourceManager->Insert<Material>(L"UIHudItem", material);
	}

	//Right Item
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"UIShader", eResTexture::UI_spr_itemicons_0);
		gResourceManager->Insert<Material>(L"UIRightItem", material);
	}

	//Left Item
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"UIShader", eResTexture::UI_spr_katanaicons_0);
		gResourceManager->Insert<Material>(L"UILeftItem", material);
	}

	//Right Click Mouse
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"UIShader", eResTexture::UI_spr_right_click_1);
		gResourceManager->Insert<Material>(L"UIRightClick", material);
	}

	//Left Click Mouse
	{
		Material* const material =
			MaterialBuilder::BuildDefault2DMaterial(
				eRenderType::Opqaue, L"UIShader", eResTexture::UI_spr_left_click_1);
		gResourceManager->Insert<Material>(L"UILeftClick", material);
	}
}

void Content::testSceneInitialize()
{
	const Vector2 screenSize = gEngine->GetScreenSize();
	Scene* testScene = new Scene();

	//BackGround parent
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"BackGround01");

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

	const float hudPosY = gEngine->GetScreenHeight() / 2.f - 23.f;

	//Mouse Cursor
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UICursor");

		obj->AddComponent<CursorMovement>();

		obj->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI UP Hud
	{
		GameObject* const obj = GameObjectBuilder::BuildDefault2DGameObject(L"UIHud");

		const Vector2 pos = helper::WindowScreenToUIPostion(Vector2(screenSize.x / 2.f, 23.f), screenSize);

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

		mainCameraObj->GetComponent<Camera>()->SetCameraType(Camera::eCameraType::Main);
		mainCameraObj->GetComponent<Camera>()->TurnOnAllLayer();
		mainCameraObj->GetComponent<Camera>()->TurnOffLayer(eLayerType::UI);
		mainCameraObj->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);

		testScene->AddGameObject(mainCameraObj, eLayerType::Default);
	}

	//UI Camera
	{
		GameObject* const mainCameraObj = new GameObject();

		mainCameraObj->AddComponent<Camera>();

		mainCameraObj->GetComponent<Camera>()->SetCameraType(Camera::eCameraType::UI);
		mainCameraObj->GetComponent<Camera>()->TurnOffAllLayer();
		mainCameraObj->GetComponent<Camera>()->TurnOnLayer(eLayerType::UI);
		mainCameraObj->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);

		testScene->AddGameObject(mainCameraObj, eLayerType::Default);
	}

	SceneManager::GetInstance()->LoadScene(testScene);
}
