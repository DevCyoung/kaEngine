#include "pch.h"
#include "ResourceManager.h"


#include "Textrue.h"

namespace engine
{
	ResourceManager::ResourceManager()
	{

	}

	ResourceManager::~ResourceManager()
	{
		for (std::unordered_map<UINT, Resource*>& item : mResources)
		{
			safe::DeleteUnorderedMap(item);
		}
	}

	void ResourceManager::initialize()
	{
		assert(!sInstance);
		sInstance = new ResourceManager();

		//sInstance->Load<Texture>(eResTexture::Fighter);

		//for (UINT i = 0; i < static_cast<UINT>(eResTexture::End); ++i)
		//{
		//	sInstance->Load<Texture>(eResTexture::Fighter);
		//}

		/*for (UINT i = 0; i < static_cast<UINT>(eResMaterial::End); ++i)
		{
			Load<Material>(static_cast<eResMaterial>(i));
		}

		for (UINT i = 0; i < static_cast<UINT>(eResMesh::End); ++i)
		{
			Load<Mesh>(static_cast<eResMesh>(i));
		}

		for (UINT i = 0; i < static_cast<UINT>(eResShader::End); ++i)
		{
			Load<Shader>(static_cast<eResShader>(i));
		}		

		for (UINT i = 0; i < static_cast<UINT>(eResAnimation::End); ++i)
		{
			Load<Animation>(static_cast<eResAnimation>(i));
		}

		for (UINT i = 0; i < static_cast<UINT>(eResFont::End); ++i)
		{
			Load<Font>(static_cast<eResFont>(i));
		}*/

		

	}

	void ResourceManager::ResourceAllLoad()
	{
		//리소스로드
		for (UINT i = 0; i < static_cast<UINT>(eResTexture::End); ++i)
		{			
			ResourceManager::GetInstance()->Load<Texture>(static_cast<eResTexture>(i));
		}

	}

}

