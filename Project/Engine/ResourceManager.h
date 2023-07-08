#pragma once
#include "Singleton.h"
#include "Resource.h"
#include "PathManager.h"
#include "ResourceTypeTrait.h"

class ResourceManager
{
	friend class Engine;
	SINGLETON_DECLARE(ResourceManager);

public:
	using Key = std::wstring;
	using Value = Resource;
	using Dictionary = std::unordered_map<Key, Value*>;
	using ConstIterator = Dictionary::const_iterator;

public:
	template<typename T>
		requires (is_engine_resource<T>::value)
	T* FindOrNull(const Key& relativePathOrName) const ;
	template<typename T>
		requires (is_engine_resource<T>::value)
	T* FindOrNullByEnum(const typename engine_resource_type<T>::eResEnumType resNameType) const ;

	template<typename T>
		requires (is_engine_resource<T>::value)
	T* Find(const Key& relativePathOrName);
	template<typename T>
		requires (is_engine_resource<T>::value)
	T* FindByEnum(const typename engine_resource_type<T>::eResEnumType resNameType);

	template <typename T>
		requires (is_engine_resource<T>::value)
	void Load(const Key& relativePathOrName);
	template <typename T>
		requires (is_engine_resource<T>::value)
	void LoadByEnum(const typename engine_resource_type<T>::eResEnumType resNameType);

	template<typename T>
		requires (is_engine_resource<T>::value)
	void Insert(const Key& relativePathOrName, T* const value);

private:
	Dictionary mResources[static_cast<UINT>(eResourceType::End)];
};
#define gResourceManager ResourceManager::GetInstance()


template<typename T>
	requires (is_engine_resource<T>::value)
inline T* ResourceManager::FindOrNull(const Key& relativePathOrName) const
{
	T* res = nullptr;

	constexpr eResourceType RES_TYPE = engine_resource_type<T>::type;
	const Dictionary& RESOURCES = mResources[static_cast<UINT>(RES_TYPE)];
	ConstIterator iter = RESOURCES.find(relativePathOrName);

	if (iter != RESOURCES.end())
	{
		res = dynamic_cast<T*>(iter->second);
		Assert(res, WCHAR_IS_NULLPTR);
	}

	return res;
}

template<typename T>
	requires (is_engine_resource<T>::value)
inline T* ResourceManager::FindOrNullByEnum(const typename engine_resource_type<T>::eResEnumType resNameType) const
{
	return FindOrNull<T>(EnumResourcePath(resNameType));
}

template<typename T>
	requires (is_engine_resource<T>::value)
inline T* ResourceManager::Find(const Key& relativePathOrName)
{
	T* resource = FindOrNull<T>(relativePathOrName);

	if (nullptr == resource)
	{
		Load<T>(relativePathOrName);
		resource = FindOrNull<T>(relativePathOrName);
	}

	Assert(resource, WCHAR_IS_NULLPTR);
	return resource;
}

template<typename T>
	requires (is_engine_resource<T>::value)
inline T* ResourceManager::FindByEnum(const typename engine_resource_type<T>::eResEnumType resNameType)
{
	return Find<T>(EnumResourcePath(resNameType));
}


template<typename T>
	requires (is_engine_resource<T>::value)
inline void ResourceManager::Load(const Key& relativePathOrName)
{
	T* resource = FindOrNull<T>(relativePathOrName);
	Assert(!resource, WCHAR_IS_NOT_NULLPTR);

	constexpr eResourceType RES_TYPE = engine_resource_type<T>::type;
	Dictionary& resources = mResources[static_cast<UINT>(RES_TYPE)];

	resource = new T();

	const std::wstring FULL_PATH = PathManager::GetInstance()->GetResourcePath() + relativePathOrName;

	resource->Load(FULL_PATH);
	resource->mRelativePath = relativePathOrName;

	resources.insert(std::make_pair(relativePathOrName, resource)); //key : relative Path
}

template<typename T>
	requires (is_engine_resource<T>::value)
inline void ResourceManager::LoadByEnum(const typename engine_resource_type<T>::eResEnumType resNameType)
{
	Load<T>(EnumResourcePath(resNameType));
}


template<typename T>
	requires (is_engine_resource<T>::value)
inline void ResourceManager::Insert(const Key& relativePathOrName, T* const value)
{
	Assert(value, WCHAR_IS_NULLPTR);
	constexpr eResourceType RES_TYPE = engine_resource_type<T>::type;

	Dictionary& resources = mResources[static_cast<UINT>(RES_TYPE)];
	ConstIterator citer = resources.find(relativePathOrName);

	Assert(resources.end() == citer, L"already");

	value->mRelativePath = relativePathOrName;

	resources.insert(std::make_pair(relativePathOrName, value));
}
