#pragma once
#include "Singleton.h"
#include "Resource.h"
#include "PathManager.h"
#include "EnumResourceType.h"

namespace engine
{
	class ResourceManager
	{
		friend class Engine;
		SINGLETON_DECLARE(ResourceManager);

	public:



		template<typename T>
		static T* FindOrNull(enable_if_resource<T>::ResEnumType resName)
		{
			constexpr eResourceType resType = enable_if_resource<T>::resourceType;
			std::unordered_map<UINT, Resource*>& resources = sInstance->mResources[static_cast<UINT>(resType)];
			std::unordered_map<UINT, Resource*>::iterator iter = resources.find(static_cast<UINT>(resName));

			T* res = nullptr;

			if (iter != resources.end())
			{
				res = dynamic_cast<T*>(iter->second);
			}

			return res;
		}

		template <typename T>
		static void Load(enable_if_resource<T>::ResEnumType resType)
		{
			T* res = FindOrNull<T>(resType);
			assert(!res);

			constexpr eResourceType type = enable_if_resource<T>::resourceType;
			std::unordered_map<UINT, Resource*>& resources = sInstance->mResources[static_cast<UINT>(type)];

			res = new T();

			std::wstring wstr = PathManager::GetInstance()->GetResourcePath();
			wstr += EnumResourcePath(resType);

			HRESULT hResult = res->Load(wstr.c_str());
			assert(!hResult);

			resources.insert(std::make_pair(static_cast<UINT>(resType), res));
		}

		template<typename T>
		static T* Find(enable_if_resource<T>::ResEnumType resName)
		{
			T* res = FindOrNull<T>(resName);

			if (nullptr == res)
			{
				Load<T>(resName);
				res = FindOrNull<T>(resName);
			}

			assert(res);
			return res;
		}



	private:		
		std::unordered_map<UINT, Resource*> mResources[static_cast<UINT>(eResourceType::End)];
	};
}