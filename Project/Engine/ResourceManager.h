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

		using Key = std::wstring;
		using Base = Resource;
		using HashMap = std::unordered_map<Key, Base*>;
		using Iterator = HashMap::iterator;
		using ConstIterator = HashMap::const_iterator;

		SINGLETON_DECLARE(ResourceManager);

	public:
		template<typename T>
			requires std::is_base_of_v<Base, T>
		T* FindOrNullByRelativePath(const Key& orName) //or Relative Path
		{
			T* res = nullptr;

			constexpr eResourceType resType = enable_if_resource<T>::resourceType;
			const HashMap& resources = mResources[static_cast<UINT>(resType)];
			ConstIterator iter = resources.find(orName);

			if (iter != resources.end())
			{
				res = dynamic_cast<T*>(iter->second);
				Assert(res, WCHAR_IS_NULLPTR);
			}

			return res;
		}

		template<typename T>
			requires std::is_base_of_v<Base, T>
		T* FindOrNullByEnum(enable_if_resource<T>::eResEnumType resName)
		{
			return FindOrNullByRelativePath<T>(EnumResourcePath(resName));
		}


		template <typename T>
			requires std::is_base_of_v<Base, T>
		void LoadByRelativePath(const Key& orName)
		{
			T* res = FindOrNullByRelativePath<T>(orName);
			Assert(!res, WCHAR_IS_NOT_NULLPTR);

			constexpr eResourceType type = enable_if_resource<T>::resourceType;
			HashMap& resources = mResources[static_cast<UINT>(type)];

			res = new T();

			const std::wstring fullPath = PathManager::GetInstance()->GetResourcePath() + orName;
			res->Load(fullPath);

			res->mKey = orName;
			res->mPath = orName;

			resources.insert(std::make_pair(orName, res)); //key : relative Path
		}

		template <typename T>
			requires std::is_base_of_v<Base, T>
		void LoadByEnum(enable_if_resource<T>::eResEnumType resType)
		{
			LoadByRelativePath<T>(EnumResourcePath(resType));
		}


		template<typename T>
			requires std::is_base_of_v<Base, T>
		T* FindByRelativePath(const Key& orName)
		{
			T* res = FindOrNullByRelativePath<T>(orName);

			if (nullptr == res)
			{
				LoadByRelativePath<T>(orName);
				res = FindOrNullByRelativePath<T>(orName);
			}

			Assert(res, WCHAR_IS_NULLPTR);
			return res;
		}


		template<typename T>
			requires std::is_base_of_v<Base, T>
		T* FindByEnum(enable_if_resource<T>::eResEnumType resName)
		{
			return FindByRelativePath<T>(EnumResourcePath(resName));
		}

		template<typename T>
			requires std::is_base_of_v<Base, T>
		void Insert(const Key& key, T* const value)
		{
			Assert(value, WCHAR_IS_NULLPTR);
			constexpr eResourceType type = enable_if_resource<T>::resourceType;
			HashMap& resources = mResources[static_cast<UINT>(type)];
			ConstIterator iter = resources.find(key);

			Assert(resources.end() == iter, L"");

			value->mKey = key;
			value->mPath = key;
			resources.insert(std::make_pair(key, value));
		}



	private:
		HashMap mResources[static_cast<UINT>(eResourceType::End)];
	};
}

#define gResourceManager engine::ResourceManager::GetInstance()