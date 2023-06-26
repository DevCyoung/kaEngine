#include "pch.h"
#include "Content.h"
#include <Engine/SceneManager.h>
#include <Engine/TimeManager.h>
#include <Engine/InputManager.h>

#include "ResourceManager.h"
#include "StructVertex.h"

#include "Components.h"

#include "CameraInputMove.h"

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

	//Texture
	{
		for (UINT i = 0; i < static_cast<UINT>(eResTexture::End); ++i)
		{
			gResourceManager->LoadByEnum<Texture>(static_cast<eResTexture>(i));
		}
	}

	////Mesh
	{
		const UINT VERTEX_COUNT = 6;

		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.ByteWidth = sizeof(tVertex) * VERTEX_COUNT;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		tVertex vertex[VERTEX_COUNT] = {};

		vertex[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertex[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertex[0].uv = Vector2(0.0f, 0.0f);

		vertex[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertex[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertex[1].uv = Vector2(1.0f, 1.0f);

		vertex[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertex[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertex[2].uv = Vector2(0.0f, 1.0f);

		vertex[3].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertex[3].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertex[3].uv = Vector2(0.0f, 0.0f);

		vertex[4].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertex[4].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertex[4].uv = Vector2(1.0f, 0.0f);

		vertex[5].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertex[5].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertex[5].uv = Vector2(1.0f, 1.0f);

		triangleData.pSysMem = vertex;


		gResourceManager->Insert<Mesh>(L"Rect",
			new Mesh(triangleDesc, &triangleData,
				sizeof(tVertex), VERTEX_COUNT));
	}

	//Shader
	{
		
		Shader* const defaultShader =
			new Shader(eResShader::VertexShader, L"main", eResShader::PixelShader, L"main");

		gResourceManager->Insert<Shader>(L"Default", defaultShader);
	}

	//Material
	{
		{
			Material* const defaultMaterial = new Material();	
			defaultMaterial->SetShader(gResourceManager
				->FindOrNullByRelativePath<Shader>(L"Default"));
			defaultMaterial->SetTexture(gResourceManager
				->FindOrNullByEnum<Texture>(eResTexture::door));

			gResourceManager->Insert<Material>(L"Default", defaultMaterial);
		}

		{
			Material* const defaultMaterial = new Material();
			defaultMaterial->SetShader(gResourceManager
				->FindOrNullByRelativePath<Shader>(L"Default"));
			defaultMaterial->SetTexture(gResourceManager
				->FindOrNullByEnum<Texture>(eResTexture::orange));

			gResourceManager->Insert<Material>(L"Sample", defaultMaterial);
		}


		{
			Material* const defaultMaterial = new Material();
			defaultMaterial->SetShader(gResourceManager
				->FindOrNullByRelativePath<Shader>(L"Default"));
			defaultMaterial->SetTexture(gResourceManager
				->FindOrNullByEnum<Texture>(eResTexture::bg_bar_0));

			gResourceManager->Insert<Material>(L"BackGround01", defaultMaterial);
		}

		{
			Material* const defaultMaterial = new Material();
			defaultMaterial->SetShader(gResourceManager
				->FindOrNullByRelativePath<Shader>(L"Default"));
			defaultMaterial->SetTexture(gResourceManager
				->FindOrNullByEnum<Texture>(eResTexture::bg_club_full_0));

			gResourceManager->Insert<Material>(L"BackGround02", defaultMaterial);
		}

		{
			Material* const defaultMaterial = new Material();
			defaultMaterial->SetShader(gResourceManager
				->FindOrNullByRelativePath<Shader>(L"Default"));
			defaultMaterial->SetTexture(gResourceManager
				->FindOrNullByEnum<Texture>(eResTexture::bg_dreamshed_0));

			gResourceManager->Insert<Material>(L"BackGround03", defaultMaterial);
		}

		{
			Material* const defaultMaterial = new Material();
			defaultMaterial->SetShader(gResourceManager
				->FindOrNullByRelativePath<Shader>(L"Default"));
			defaultMaterial->SetTexture(gResourceManager
				->FindOrNullByEnum<Texture>(eResTexture::bg_studio_outside_0));

			gResourceManager->Insert<Material>(L"BackGround04", defaultMaterial);
		}

		{
			Material* const defaultMaterial = new Material();
			defaultMaterial->SetShader(gResourceManager
				->FindOrNullByRelativePath<Shader>(L"Default"));
			defaultMaterial->SetTexture(gResourceManager
				->FindOrNullByEnum<Texture>(eResTexture::spr_bg_neighbor_apartment_0));

			gResourceManager->Insert<Material>(L"BackGround05", defaultMaterial);
		}

	}


}

void Content::testSceneInitialize()
{
	Scene* testScene = new Scene();

	{
		//change

		
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
				->FindOrNullByRelativePath<Material>(L"BackGround01"));

		obj->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		
		Texture* const texture = obj->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture();
		const float textureWidth = texture->GetWidth();
		const float textureHeigth = texture->GetHeight();
		obj->GetComponent<Transform>()->SetScale(textureWidth * 0.018f, textureHeigth * 0.018f, 1.f);
		
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

		obj->GetComponent<Transform>()->SetPosition(20.f, 0.f, 0.f);

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
		//test2
		//for (int i = 0; i < 5000; ++i)
		//{
		//	GameObject* const obj = new GameObject();
		//	obj->AddComponent<MeshRenderer>();
		//
		//	obj->GetComponent<MeshRenderer>()
		//		->SetMesh(gResourceManager
		//			->FindOrNullByRelativePath<Mesh>(L"Rect"));
		//
		//	obj->GetComponent<MeshRenderer>()
		//		->SetMaterial(gResourceManager
		//			->FindOrNullByRelativePath<Material>(L"Sample"));
		//
		//	obj->GetComponent<Transform>()
		//		->SetPosition(-4.f + i * 0.02f, -4.f + i * 0.02f, 0.f);
		//
		//	testScene->AddGameObject(obj, eLayerType::Player);
		//}

	} //Scene


	{
		GameObject* const mainCameraObj = new GameObject();
		mainCameraObj->AddComponent<Camera>();
		mainCameraObj->AddComponent<CameraInputMove>();


		Camera* const cameraComp = mainCameraObj->GetComponent<Camera>();
		mainCameraObj->GetComponent<Transform>()->SetPosition(0.f, 0.f, -10.f);
		(void)cameraComp;


		//FIXME 카메라가 씬에없는데도 가져올수있게됨 고쳐야함!
		Camera::SetMainCamera(cameraComp);
		testScene->AddGameObject(mainCameraObj, eLayerType::Player);
	}

	SceneManager::GetInstance()->LoadScene(testScene);
}
