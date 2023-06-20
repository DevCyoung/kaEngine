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
		using HashMap = std::unordered_map<std::wstring, Resource*>;
		using Iterator = HashMap::iterator;
		using ConstIterator = HashMap::const_iterator;
		SINGLETON_DECLARE(ResourceManager);

	public:
		template<typename T>
		static T* FindOrNullByRelativePath(const std::wstring& orName) //or Relative Path
		{
			constexpr eResourceType resType = enable_if_resource<T>::resourceType;
			const HashMap& resources = sInstance->mResources[static_cast<UINT>(resType)];
			ConstIterator iter = resources.find(orName);

			T* res = nullptr;

			if (iter != resources.end())
			{
				res = dynamic_cast<T*>(iter->second);
				assert(res);		
			}

			return res;
		}

		template<typename T>
		static T* FindOrNullByEnum(enable_if_resource<T>::ResEnumType resName)
		{
			return FindOrNullByRelativePath<T>(EnumResourcePath(resName));
		}


		template <typename T>
		static void LoadByRelativePath(const std::wstring& orName)
		{
			T* res = FindOrNullByRelativePath<T>(orName);
			assert(!res);

			constexpr eResourceType type = enable_if_resource<T>::resourceType;
			HashMap& resources = sInstance->mResources[static_cast<UINT>(type)];

			res = new T();

			const std::wstring fullPath = PathManager::GetInstance()->GetResourcePath() + orName;
			res->Load(fullPath);

			res->mKey = orName;
			res->mPath = orName;
			
			resources.insert(std::make_pair(orName, res)); //key : relative Path
		}

		template <typename T>
		static void LoadByEnum(enable_if_resource<T>::ResEnumType resType)
		{
			LoadByRelativePath<T>(EnumResourcePath(resType));
		}


		template<typename T>
		static T* FindByRelativePath(const std::wstring& orName)
		{
			T* res = FindOrNullByRelativePath<T>(orName);

			if (nullptr == res)
			{
				LoadByRelativePath<T>(orName);
				res = FindOrNullByRelativePath<T>(orName);
			}

			assert(res);
			return res;
		}


		template<typename T>
		static T* FindByEnum(enable_if_resource<T>::ResEnumType resName)
		{
			return FindByRelativePath<T>(EnumResourcePath(resName));
		}

		template<typename T>
		static void Insert(const std::wstring& key, T* const value)
		{
			assert(value);
			constexpr eResourceType type = enable_if_resource<T>::resourceType;
			HashMap& resources = sInstance->mResources[static_cast<UINT>(type)];
			Iterator iter = resources.find(key);

			assert(resources.end() == iter);
			resources.insert(std::make_pair(key, value));
		}



	private:
		HashMap mResources[static_cast<UINT>(eResourceType::End)];
	};
}

#define gResourceManager engine::ResourceManager::GetInstance()