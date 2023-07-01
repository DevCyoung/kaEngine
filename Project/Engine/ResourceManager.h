#pragma once
#include "Singleton.h"
#include "Resource.h"
#include "PathManager.h"
#include "ResourceTypeTrait.h"

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
		requires (is_engine_resource<T>::value)
	T* FindOrNullByRelativePath(const Key& orName); //or Relative Path
	template<typename T>
		requires (is_engine_resource<T>::value)
	T* FindOrNullByEnum(engine_resource_type<T>::eResEnumType resName);

	template<typename T>
		requires (is_engine_resource<T>::value)
	T* FindByRelativePath(const Key& orName);
	template<typename T>
		requires (is_engine_resource<T>::value)
	T* FindByEnum(engine_resource_type<T>::eResEnumType resName);

	template <typename T>
		requires (is_engine_resource<T>::value)
	void LoadByRelativePath(const Key& orName);
	template <typename T>
		requires (is_engine_resource<T>::value)
	void LoadByEnum(engine_resource_type<T>::eResEnumType resType);

	template<typename T>
		requires (is_engine_resource<T>::value)
	void Insert(const Key& key, T* const value);

private:
	HashMap mResources[static_cast<UINT>(eResourceType::End)];
};
#define gResourceManager ResourceManager::GetInstance()


template<typename T>
	requires (is_engine_resource<T>::value)
inline T* ResourceManager::FindOrNullByRelativePath(const Key& orName)
{
	
		T* res = nullptr;

		constexpr eResourceType resType = engine_resource_type<T>::resourceType;
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
	requires (is_engine_resource<T>::value)
inline T* ResourceManager::FindOrNullByEnum(engine_resource_type<T>::eResEnumType resName)
{
	return FindOrNullByRelativePath<T>(EnumResourcePath(resName));
}

template<typename T>
	requires (is_engine_resource<T>::value)
inline void ResourceManager::LoadByRelativePath(const Key& orName)
{
	T* res = FindOrNullByRelativePath<T>(orName);
	Assert(!res, WCHAR_IS_NOT_NULLPTR);

	constexpr eResourceType type = engine_resource_type<T>::resourceType;
	HashMap& resources = mResources[static_cast<UINT>(type)];

	res = new T();

	const std::wstring fullPath = PathManager::GetInstance()->GetResourcePath() + orName;
	res->Load(fullPath);

	res->mKey = orName;
	res->mPath = orName;

	resources.insert(std::make_pair(orName, res)); //key : relative Path
}

template<typename T>
	requires (is_engine_resource<T>::value)
inline void ResourceManager::LoadByEnum(engine_resource_type<T>::eResEnumType resType)
{
	LoadByRelativePath<T>(EnumResourcePath(resType));
}

template<typename T>
	requires (is_engine_resource<T>::value)
inline T* ResourceManager::FindByRelativePath(const Key& orName)
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
	requires (is_engine_resource<T>::value)
inline T* ResourceManager::FindByEnum(engine_resource_type<T>::eResEnumType resName)
{
	return FindByRelativePath<T>(EnumResourcePath(resName));
}

template<typename T>
	requires (is_engine_resource<T>::value)
inline void ResourceManager::Insert(const Key& key, T* const value)
{
	Assert(value, WCHAR_IS_NULLPTR);
	constexpr eResourceType type = engine_resource_type<T>::resourceType;
	HashMap& resources = mResources[static_cast<UINT>(type)];
	ConstIterator iter = resources.find(key);

	Assert(resources.end() == iter, L"already");

	value->mKey = key;
	value->mPath = key;
	resources.insert(std::make_pair(key, value));
}
