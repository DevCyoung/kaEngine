#include "pch.h"
#include <Engine/Engine.h>
#include <Engine/GraphicDeviceDx11.h>
#include <Engine/Scene.h>
#include <Engine/SceneManager.h>
#include <Engine/GameObject.h>
#include <Engine/Transform.h>
#include <Engine/MeshRenderer.h>
#include <Engine/Mesh.h>
#include <Engine/Material.h>
#include <Engine/Textrue.h>
#include <Engine/Material.h>
#include <Engine/Shader.h>
#include <Engine/ResourceManager.h>
#include <Engine/CBCollection.h>

#include "Content.h"
#include "SampleScript.h"
#include "EnumResourceTypeAnimation.h"	
#include "EnumResourceTypeFont.h"
#include "EnumResourceTypeScene.h"
#include "EnumResourceTypeMaterial.h"
#include "EnumResourceTypeMesh.h"
#include "EnumResourceTypeShader.h"
#include "EnumResourceTypeSound.h"
#include "EnumResourceTypeTexture.h"

namespace content
{

	using namespace engine;


	Content::Content()
	{
	}


	Content::~Content()
	{
	}

	void Content::initialize()
	{			
		//Reosurece Load
		{
			//Texture Load
			{
				for (UINT i = 0; i < static_cast<UINT>(eResTexture::End); ++i)
				{
					gResourceManager->LoadByEnum<Texture>(static_cast<eResTexture>(i));
				}							
			}			

			//Shader
			{
				Shader* const defaultShader =
					new Shader(
						eResShader::VertexShader, L"main",
						eResShader::PixelShader, L"main",
						gEngine->GetGraphicDevice()->UnSafe_GetDevice(),
						gEngine->GetHwnd());
				gResourceManager->Insert<Shader>(L"Default", defaultShader);				
			}

			//Material
			{
				Material* const defaultMaterial = new Material();
				defaultMaterial->SetShader(gResourceManager
					->FindOrNullByRelativePath<Shader>(L"Default"));
				defaultMaterial->SetTexture(gResourceManager
					->FindOrNullByEnum<Texture>(eResTexture::walk));
				gResourceManager->Insert<Material>(L"Default", defaultMaterial);				
			}
		}

		Scene* testScene = new Scene();
		//test
		GameObject* const obj = new GameObject();
		obj->AddComponent<MeshRenderer>();
		obj->AddComponent<SampleScript>();

		obj->GetComponent<MeshRenderer>()
			->SetMesh(gResourceManager
				->FindOrNullByRelativePath<Mesh>(L"Rect"));

		obj->GetComponent<MeshRenderer>()
			->SetMaterial(gResourceManager
				->FindOrNullByRelativePath<Material>(L"Default"));

		testScene->AddGameObject(obj, eLayerType::Player);
		SceneManager::GetInstance()->LoadScene(testScene);


		assert(!sInstance);
		sInstance = new Content();
	}
}

