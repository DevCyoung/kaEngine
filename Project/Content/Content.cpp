#include "pch.h"
#include "Content.h"
#include <Engine/SceneManager.h>
#include <Engine/TimeManager.h>
#include <Engine/InputManager.h>

#include "ResourceManager.h"
#include "StructVertex.h"

#include "Components.h"

#include "CameraInputMove.h"
#include <Engine/Tanning.h>

#include "Bugiman.h"

#include <Engine/RenderManager.h>
#include <Engine/Engine.h>

#include "CursorMovement.h"

Content::Content()
{
	resourceInitialize();
	testSceneInitialize();
}

Content::~Content()
{
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
				eDSType::NoWrite,
				eBSType::AlphaBlend);
		gResourceManager->Insert<Shader>(L"UIShader", UIShader);
	}

}

void Content::loadTexture()
{
	for (UINT i = 0; i < static_cast<UINT>(eResTexture::End); ++i)
	{
		gResourceManager->LoadByEnum<Texture>(static_cast<eResTexture>(i));
	}
}

void Content::loadMaterial()
{
	loadUIMaterial();

	{
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::door));

		gResourceManager->Insert<Material>(L"Default", material);
	}

	{
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::orange));

		gResourceManager->Insert<Material>(L"Sample", material);
	}


	{
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::bg_club_full_0));

		gResourceManager->Insert<Material>(L"BackGround01", material);
	}

	{
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::door));

		gResourceManager->Insert<Material>(L"Door", material);
	}

	{
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::bg_club_full_0));

		gResourceManager->Insert<Material>(L"BackGround02", material);
	}

	{
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::bg_dreamshed_0));

		gResourceManager->Insert<Material>(L"BackGround03", material);
	}

	{
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::bg_studio_outside_0));

		gResourceManager->Insert<Material>(L"BackGround04", material);
	}

	{
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::spr_bg_neighbor_apartment_0));

		gResourceManager->Insert<Material>(L"BackGround05", material);
	}

}




void Content::loadUIMaterial()
{
	{
		//Hud
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"UIShader"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::UI_spr_hud));

		gResourceManager->Insert<Material>(L"UIHud", material);
	}

	{
		//Hud Timer
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"UIShader"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::UI_spr_hud_timer_0));

		gResourceManager->Insert<Material>(L"UIHudTimer", material);
	}

	{
		//Timer
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"UIShader"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::UI_spr_timer));

		gResourceManager->Insert<Material>(L"UITimer", material);
	}


	{
		//Shift
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"UIShader"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::UI_spr_keyboard_shift_0));

		gResourceManager->Insert<Material>(L"UIShift", material);
	}

	{
		//Shift
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"UIShader"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::UI_spr_hud_battery));

		gResourceManager->Insert<Material>(L"UIBattery", material);
	}


	{
		//Item Board
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"UIShader"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::UI_spr_hud_subweapon));

		gResourceManager->Insert<Material>(L"UIHudItem", material);
	}

	{
		//Left Item
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"UIShader"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::UI_spr_itemicons_0));

		gResourceManager->Insert<Material>(L"UIRightItem", material);
	}

	{
		//Right Item
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"UIShader"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::UI_spr_katanaicons_0));

		gResourceManager->Insert<Material>(L"UILeftItem", material);
	}



	{
		//Left Mouse
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"UIShader"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::UI_spr_left_click_1));

		gResourceManager->Insert<Material>(L"UILeftClick", material);
	}

	{
		//Right Mouse
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"UIShader"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::UI_spr_right_click_1));

		gResourceManager->Insert<Material>(L"UIRightClick", material);
	}




	{
		//Cursor
		Material* const material = new Material(eRenderType::Opqaue);
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"UIShader"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::UI_spr_cursor));

		gResourceManager->Insert<Material>(L"UICursor", material);
	}




}





void Content::resourceInitialize()
{
	loadMesh();
	loadTexture();
	loadShader();
	loadMaterial();
}

void Content::testSceneInitialize()
{
	Scene* testScene = new Scene();


	{
		//test
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();
		obj->AddComponent<Bugiman>();
	
	
		//obj->AddComponent(new ScriptComponent(eScriptComponentType::Bugiman));
	
		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));
	
		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"BackGround01"));
	
		obj->GetComponent<Transform>()
			->SetPosition(0.f, 0.f, 15.f);

		obj->GetComponent<Transform>()
			->SetScale(2.f, 2.f, 1.f);
	
		testScene->AddGameObject(obj, eLayerType::Default);
	}




	const float hudPosY = gEngine->GetScreenHeight() / 2.f - 23.f;

	//Cursor
	{

		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();
		obj->AddComponent<CursorMovement>();


		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));
		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"UICursor"));

		obj->GetComponent<Transform>()
			->SetPosition(610.f, hudPosY - 24.f, -10.f);

		obj->GetComponent<Transform>()
			->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI
	{
		//Hud
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));
		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"UIHud"));

		obj->GetComponent<Transform>()
			->SetPosition(0, hudPosY, -10.f);

		obj->GetComponent<Transform>()
			->SetScale(2.f, 2.f, 1.f);


		testScene->AddGameObject(obj, eLayerType::UI);
	}

	const float timerPosX = -8.f;
	{
		//UIHudTimer
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));
		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"UIHudTimer"));

		obj->GetComponent<Transform>()
			->SetPosition(timerPosX, hudPosY + 2.f, -10.f);

		obj->GetComponent<Transform>()
			->SetScale(2.f, 2.f, 1.f);


		testScene->AddGameObject(obj, eLayerType::UI);
	}


	{
		//Timer
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));
		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"UITimer"));

		obj->GetComponent<Transform>()
			->SetPosition(timerPosX + 16.f, hudPosY + 6.f, -10.f);

		obj->GetComponent<Transform>()
			->SetScale(2.f, 2.f, 1.f);


		testScene->AddGameObject(obj, eLayerType::UI);
	}


	//UIShift
	{		
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));
		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"UIShift"));

		obj->GetComponent<Transform>()
			->SetPosition(-455.f, hudPosY + 1.f, -10.f);

		obj->GetComponent<Transform>()
			->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Battery
	{
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));
		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"UIBattery"));

		obj->GetComponent<Transform>()
			->SetPosition(-561.f, hudPosY - 1.f, -10.f);

		obj->GetComponent<Transform>()
			->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}



	//UI Hud Item
	{		
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));
		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"UIHudItem"));

		obj->GetComponent<Transform>()
			->SetPosition(+560.f, hudPosY + 1.f, -10.f);

		obj->GetComponent<Transform>()
			->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}


	//UI Left Item
	{
		//Timer
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));
		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"UILeftItem"));

		obj->GetComponent<Transform>()
			->SetPosition(528.f, hudPosY + 1.f, -10.f);

		obj->GetComponent<Transform>()
			->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Right Item
	{
		//Timer
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));
		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"UIRightItem"));

		obj->GetComponent<Transform>()
			->SetPosition(592.f, hudPosY + 1.f, -10.f);

		obj->GetComponent<Transform>()
			->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Left Click
	{
		//Timer
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));
		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"UILeftClick"));

		obj->GetComponent<Transform>()
			->SetPosition(550.f, hudPosY - 24.f, -10.f);

		obj->GetComponent<Transform>()
			->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}

	//UI Right Click
	{		
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));
		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"UIRightClick"));

		obj->GetComponent<Transform>()
			->SetPosition(610.f, hudPosY - 24.f, -10.f);

		obj->GetComponent<Transform>()
			->SetScale(2.f, 2.f, 1.f);

		testScene->AddGameObject(obj, eLayerType::UI);
	}




	//
	//{
	//	//test
	//	GameObject* const obj = new GameObject();
	//	obj->AddComponent<MeshRenderer>();
	//
	//	obj->GetComponent<MeshRenderer>()
	//		->SetMesh(gResourceManager
	//			->FindOrNullByRelativePath<Mesh>(L"Rect"));
	//
	//	obj->GetComponent<MeshRenderer>()
	//		->SetMaterial(gResourceManager
	//			->FindOrNullByRelativePath<Material>(L"BackGround02"));
	//
	//	obj->GetComponent<Transform>()
	//		->SetPosition(20.f, 0.f, 0.f);
	//
	//	Texture* const texture = obj->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture();
	//	const float textureWidth = texture->GetWidth();
	//	const float textureHeigth = texture->GetHeight();
	//	obj->GetComponent<Transform>()->SetScale(textureWidth * 0.01f, textureHeigth * 0.01f, 1.f);
	//
	//	testScene->AddGameObject(obj, eLayerType::Player);
	//}
	//
	//
	//{
	//
	//	//test
	//	GameObject* const obj = new GameObject();
	//	obj->AddComponent<MeshRenderer>();
	//
	//	obj->GetComponent<MeshRenderer>()
	//		->SetMesh(gResourceManager
	//			->FindOrNullByRelativePath<Mesh>(L"Rect"));
	//
	//	obj->GetComponent<MeshRenderer>()
	//		->SetMaterial(gResourceManager
	//			->FindOrNullByRelativePath<Material>(L"BackGround03"));
	//
	//	obj->GetComponent<Transform>()->SetPosition(32.f, 0.f, 0.f);
	//
	//	Texture* const texture = obj->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture();
	//	const float textureWidth = texture->GetWidth();
	//	const float textureHeigth = texture->GetHeight();
	//	obj->GetComponent<Transform>()->SetScale(textureWidth * 0.013f, textureHeigth * 0.013f, 1.f);
	//
	//	testScene->AddGameObject(obj, eLayerType::Player);
	//}
	//
	//{
	//	//test
	//	GameObject* const obj = new GameObject();
	//	obj->AddComponent<MeshRenderer>();
	//
	//	obj->GetComponent<MeshRenderer>()
	//		->SetMesh(gResourceManager
	//			->FindOrNullByRelativePath<Mesh>(L"Rect"));
	//
	//	obj->GetComponent<MeshRenderer>()
	//		->SetMaterial(gResourceManager
	//			->FindOrNullByRelativePath<Material>(L"BackGround04"));
	//
	//	obj->GetComponent<Transform>()->SetPosition(40, 0.f, 0.f);
	//
	//	Texture* const texture = obj->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture();
	//	const float textureWidth = texture->GetWidth();
	//	const float textureHeigth = texture->GetHeight();
	//	obj->GetComponent<Transform>()->SetScale(textureWidth * 0.01f, textureHeigth * 0.01f, 1.f);
	//
	//	testScene->AddGameObject(obj, eLayerType::Player);
	//}
	//
	//{
	//	//test
	//	GameObject* const obj = new GameObject();
	//	obj->AddComponent<MeshRenderer>();
	//
	//	obj->GetComponent<MeshRenderer>()
	//		->SetMesh(gResourceManager
	//			->FindOrNullByRelativePath<Mesh>(L"Rect"));
	//
	//	obj->GetComponent<MeshRenderer>()
	//		->SetMaterial(gResourceManager
	//			->FindOrNullByRelativePath<Material>(L"BackGround05"));
	//
	//	Texture* const texture = obj->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture();
	//	const float textureWidth = texture->GetWidth();
	//	const float textureHeigth = texture->GetHeight();
	//	obj->GetComponent<Transform>()->SetScale(textureWidth * 0.01f, textureHeigth * 0.01f, 1.f);
	//
	//	obj->GetComponent<Transform>()->SetPosition(50, 0.f, 0.f);
	//
	//	testScene->AddGameObject(obj, eLayerType::Player);
	//}

	//Main Camera
	{
		GameObject* const mainCameraObj = new GameObject();
		mainCameraObj->AddComponent<Camera>();
		mainCameraObj->AddComponent<CameraInputMove>();

		mainCameraObj->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);


		mainCameraObj->GetComponent<Camera>()->SetCameraType(Camera::eCameraType::Main);

		mainCameraObj->GetComponent<Camera>()->TurnOnAllLayer();
		mainCameraObj->GetComponent<Camera>()->TurnOffLayer(eLayerType::UI);

		testScene->AddGameObject(mainCameraObj, eLayerType::Default);
		//이후에 사용할수도있음

	}


	//UI Camera
	{
		GameObject* const mainCameraObj = new GameObject();
		mainCameraObj->AddComponent<Camera>();		
	
		mainCameraObj->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
	
		mainCameraObj->GetComponent<Camera>()->SetCameraType(Camera::eCameraType::UI);
		mainCameraObj->GetComponent<Camera>()->TurnOffAllLayer();
		mainCameraObj->GetComponent<Camera>()->TurnOnLayer(eLayerType::UI);
	
		testScene->AddGameObject(mainCameraObj, eLayerType::Default);				
	}

	SceneManager::GetInstance()->LoadScene(testScene);
}
