#include "pch.h"
#include <Engine/Scene.h>
#include <Engine/SceneManager.h>
#include "StructVertex.h"
#include "Content.h"
#include "SampleScript.h"
#include "ResourceManager.h"

#include "Components.h"

namespace content
{
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

		//Mesh
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
		}


	}

	void Content::testSceneInitialize()
	{
		Scene* testScene = new Scene();
		{
			//test
			GameObject* const obj = new GameObject();
			obj->AddComponent<MeshRenderer>();
			//obj->AddComponent<SampleScript>();

			for (UINT i = 0; i < static_cast<UINT>(eScriptType::End); ++i)
			{
				const wchar_t* wstr = GetComponentWstrByEnum(static_cast<eScriptType>(i));
				(void)wstr;
				int a = 0;
				(void)a;
			}
			


			//obj->GetComponent<SampleScript>();
			//obj->GetComponent<OhterCameraScript>();
			SampleScript* ss = obj->GetComponentOrNull<SampleScript>();
			obj->GetComponentOrNull<MeshRenderer>();
			(void)ss;
			//script_type<Scene>::
			
				for (UINT i = 0; i < static_cast<UINT>(eScriptType::End); i++)
				{
					//eScriptType type = static_cast<eScriptType>(i);
					//script_component_name<eScriptType::CameraScript>::value;
					//script_component_type;
					//script_component_type<OhterCameraScript>::
					//script_component_name<0>::value;
					//sciript_component_name<i> a;


					//sciript_component_name<1>::value


				}





			obj->GetComponent<MeshRenderer>()
				->SetMesh(gResourceManager
					->FindOrNullByRelativePath<Mesh>(L"Rect"));

			obj->GetComponent<MeshRenderer>()
				->SetMaterial(gResourceManager
					->FindOrNullByRelativePath<Material>(L"Default"));
			obj->GetComponent<Transform>()->SetPosition(2.f, 0.f, 0.f);

			testScene->AddGameObject(obj, eLayerType::Player);
		}

		{
			//test2
			for (int i = 0; i < 1000; ++i)
			{
				GameObject* const obj = new GameObject();
				obj->AddComponent<MeshRenderer>();
				obj->AddComponent<SampleScript>();
				

				


				obj->GetComponent<MeshRenderer>()
					->SetMesh(gResourceManager
						->FindOrNullByRelativePath<Mesh>(L"Rect"));

				obj->GetComponent<MeshRenderer>()
					->SetMaterial(gResourceManager
						->FindOrNullByRelativePath<Material>(L"Sample"));

				obj->GetComponent<Transform>()
					->SetPosition(-4.f + i * 0.02f, -4.f + i * 0.02f, 0.f);


				//obj->GetComponent<>();

				SampleScript* script = obj->GetComponent<SampleScript>();
				(void)script;

				testScene->AddGameObject(obj, eLayerType::Player);
			}

		} //Scene


		{
			GameObject* const mainCameraObj = new GameObject();
			mainCameraObj->AddComponent<Camera>();
			

			Camera* const cameraComp = mainCameraObj->GetComponent<Camera>();
			mainCameraObj->GetComponent<Transform>()
				->SetPosition(0.f, 0.f, -10.f);

			//FIXME 카메라가 씬에없는데도 가져올수있게됨 고쳐야함!
			Camera::SetMainCamera(cameraComp);

			testScene->AddGameObject(mainCameraObj, eLayerType::Player);
		}

		SceneManager::GetInstance()->LoadScene(testScene);
	}
}

