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
		vertexs[0].pos		= Vector3(-0.5f, 0.5f, 0.0f);
		vertexs[0].color	= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexs[0].uv		= Vector2(0.0f, 0.0f);

		vertexs[1].pos		= Vector3(0.5f, 0.5f, 0.0f);
		vertexs[1].color	= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexs[1].uv		= Vector2(1.0f, 0.0f);

		vertexs[2].pos		= Vector3(+0.5f, -0.5f, 0.0f);
		vertexs[2].color	= Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexs[2].uv		= Vector2(1.0f, 1.0f);

		vertexs[3].pos		= Vector3(-0.5f, -0.5f, 0.0f);
		vertexs[3].color	= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexs[3].uv		= Vector2(0.0f, 1.0f);
		
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
	//Shader
	{
		Shader* const defaultShader =
			new Shader(eResShader::VertexShader, L"main",
				eResShader::PixelShader, L"main",
				eRSType::SolidBack,
				eDSType::Less,
				eBSType::Default);
		gResourceManager->Insert<Shader>(L"Default", defaultShader);
	}

	{
		Shader* const defaultShader =
			new Shader(eResShader::VertexShader, L"main",
				eResShader::PixelShader, L"main",
				eRSType::SolidBack,
				eDSType::Less,
				eBSType::AlphaBlend);
		gResourceManager->Insert<Shader>(L"Default_Copy", defaultShader);
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
	{
		Material* const material = new Material();
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::door));

		gResourceManager->Insert<Material>(L"Default", material);
	}

	{
		Material* const material = new Material();
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::orange));

		gResourceManager->Insert<Material>(L"Sample", material);
	}


	{
		Material* const material = new Material();
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::bg_bar_0));		

		gResourceManager->Insert<Material>(L"BackGround01", material);
	}

	{
		Material* const material = new Material();
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::bg_club_full_0));

		gResourceManager->Insert<Material>(L"BackGround02", material);
	}

	{
		Material* const material = new Material();
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::bg_dreamshed_0));

		gResourceManager->Insert<Material>(L"BackGround03", material);
	}

	{
		Material* const material = new Material();
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::bg_studio_outside_0));

		gResourceManager->Insert<Material>(L"BackGround04", material);
	}

	{
		Material* const material = new Material();
		material->SetShader(gResourceManager
			->FindOrNullByRelativePath<Shader>(L"Default"));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(eResTexture::spr_bg_neighbor_apartment_0));

		gResourceManager->Insert<Material>(L"BackGround05", material);
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

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));

		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"BackGround01"));				

		obj->GetComponent<Transform>()
			->SetPosition(0.f, 0.f, 0.f);
		
		Texture* const texture = obj->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture();
		const float textureWidth = texture->GetWidth();
		const float textureHeigth = texture->GetHeight();

		obj->GetComponent<Transform>()
			->SetScale(textureWidth * 0.018f, textureHeigth * 0.018f, 1.f);

		testScene->AddGameObject(obj, eLayerType::Player);		
	}

	{
		//test
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));

		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"BackGround02"));

		obj->GetComponent<Transform>()
			->SetPosition(20.f, 0.f, 0.f);

		Texture* const texture = obj->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture();
		const float textureWidth = texture->GetWidth();
		const float textureHeigth = texture->GetHeight();
		obj->GetComponent<Transform>()->SetScale(textureWidth * 0.01f, textureHeigth * 0.01f, 1.f);

		testScene->AddGameObject(obj, eLayerType::Player);
	}


	{

		//test
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));

		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"BackGround03"));

		obj->GetComponent<Transform>()->SetPosition(32.f, 0.f, 0.f);

		Texture* const texture = obj->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture();
		const float textureWidth = texture->GetWidth();
		const float textureHeigth = texture->GetHeight();
		obj->GetComponent<Transform>()->SetScale(textureWidth * 0.013f, textureHeigth * 0.013f, 1.f);

		testScene->AddGameObject(obj, eLayerType::Player);
	}

	{
		//test
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));

		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"BackGround04"));
		obj->GetComponent<Transform>()->SetPosition(40, 0.f, 0.f);

		Texture* const texture = obj->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture();
		const float textureWidth = texture->GetWidth();
		const float textureHeigth = texture->GetHeight();
		obj->GetComponent<Transform>()->SetScale(textureWidth * 0.01f, textureHeigth * 0.01f, 1.f);

		testScene->AddGameObject(obj, eLayerType::Player);
	}

	{
		//test
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));

		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"BackGround05"));

		Texture* const texture = obj->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture();
		const float textureWidth = texture->GetWidth();
		const float textureHeigth = texture->GetHeight();
		obj->GetComponent<Transform>()->SetScale(textureWidth * 0.01f, textureHeigth * 0.01f, 1.f);

		obj->GetComponent<Transform>()->SetPosition(50, 0.f, 0.f);

		testScene->AddGameObject(obj, eLayerType::Player);
	}

	{				
		GameObject* const mainCameraObj = new GameObject();
		mainCameraObj->AddComponent<Camera>();
		mainCameraObj->AddComponent<CameraInputMove>();

		Camera::SetMainCamera(mainCameraObj->GetComponent<Camera>());
		mainCameraObj->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);		
		
		//FIXME 카메라가 씬에없는데도 가져올수있게됨 고쳐야함!
		testScene->AddGameObject(mainCameraObj, eLayerType::Player);
	}

	SceneManager::GetInstance()->LoadScene(testScene);



	//{
	//	//component
	//	GameObject* const obj = new GameObject();
	//	for (UINT i = 0; i < static_cast<UINT>(eComponentType::End); ++i)
	//	{
	//		const eComponentType type = static_cast<eComponentType>(i);
	//		std::wstring  componentName = GetComponentName(type);

	//		//Add click 했을때
	//		//이미있다면 추가X
	//		if (nullptr == obj->GetComponentOrNull(type))
	//		{
	//			Component* const component = CreateComponentByEnum(type);
	//			obj->AddComponent(component);
	//		}

	//		//Remove Click 했을떄
	//		//있	어야 삭제
	//		//if (nullptr != obj->GetComponentOrNull(type))
	//		//{
	//		//	//obj->
	//		//	obj->RemoveComponent(type);
	//		//}			
	//	}

	//	//script
	//	for (UINT i = 0; i < static_cast<UINT>(eScriptComponentType::End); ++i)
	//	{
	//		const eScriptComponentType type = static_cast<eScriptComponentType>(i);
	//		std::wstring componentName =  GetScriptComponentName(type);

	//		//Add click 했을때
	//		if (nullptr == obj->GetComponentOrNull(type))
	//		{
	//			ScriptComponent* const ScriptComponent = CreateScriptComponentByEnum(type);
	//			obj->AddComponent(ScriptComponent);
	//		}

	//		//Remove Click 했을떄
	//		//if (nullptr != obj->GetComponentOrNull(type))
	//		//{
	//		//	//obj->
	//		//	obj->RemoveComponent(type);
	//		//}

	//	}

	//	testScene->AddGameObject(obj, eLayerType::Player);
	//}
}
