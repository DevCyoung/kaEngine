#pragma once
#include "Singleton.h"
#include "Resource.h"
#include "PathManager.h"
#include "ResourceTypeTrait.h"

struct tVertex
{
	Vector3 pos;
	Vector4 color;
	Vector2 uv;
	Vector2 worldPos;
};


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
	T* FindOrNull(const Key& RELATIVE_PATH_OR_NAME) const ; //or Relative Path
	template<typename T>
		requires (is_engine_resource<T>::value)
	T* FindOrNullByEnum(engine_resource_type<T>::eResEnumType resName) const ;

	template<typename T>
		requires (is_engine_resource<T>::value)
	T* Find(const Key& RELATIVE_PATH_OR_NAME);
	template<typename T>
		requires (is_engine_resource<T>::value)
	T* FindByEnum(engine_resource_type<T>::eResEnumType resName);

	template <typename T>
		requires (is_engine_resource<T>::value)
	void Load(const Key& RELATIVE_PATH_OR_NAME);
	template <typename T>
		requires (is_engine_resource<T>::value)
	void LoadByEnum(engine_resource_type<T>::eResEnumType resType);

	template<typename T>
		requires (is_engine_resource<T>::value)
	void Insert(const Key& RELATIVE_PATH_OR_NAME, T* const value);

private:
	Dictionary mResources[static_cast<UINT>(eResourceType::End)];
};
#define gResourceManager ResourceManager::GetInstance()


template<typename T>
	requires (is_engine_resource<T>::value)
inline T* ResourceManager::FindOrNull(const Key& RELATIVE_PATH_OR_NAME) const
{
	T* res = nullptr;

	constexpr eResourceType RES_TYPE = engine_resource_type<T>::type;
	const Dictionary& RESOURCES = mResources[static_cast<UINT>(RES_TYPE)];
	ConstIterator iter = RESOURCES.find(RELATIVE_PATH_OR_NAME);

	if (iter != RESOURCES.end())
	{
		res = dynamic_cast<T*>(iter->second);
		Assert(res, WCHAR_IS_NULLPTR);
	}

	return res;
}

template<typename T>
	requires (is_engine_resource<T>::value)
inline T* ResourceManager::FindOrNullByEnum(engine_resource_type<T>::eResEnumType resName) const
{
	return FindOrNull<T>(EnumResourcePath(resName));
}

template<typename T>
	requires (is_engine_resource<T>::value)
inline T* ResourceManager::Find(const Key& RELATIVE_PATH_OR_NAME)
{
	T* res = FindOrNull<T>(RELATIVE_PATH_OR_NAME);

	if (nullptr == res)
	{
		Load<T>(RELATIVE_PATH_OR_NAME);
		res = FindOrNull<T>(RELATIVE_PATH_OR_NAME);
	}

	Assert(res, WCHAR_IS_NULLPTR);
	return res;
}

template<typename T>
	requires (is_engine_resource<T>::value)
inline T* ResourceManager::FindByEnum(engine_resource_type<T>::eResEnumType resName)
{
	return Find<T>(EnumResourcePath(resName));
}


template<typename T>
	requires (is_engine_resource<T>::value)
inline void ResourceManager::Load(const Key& RELATIVE_PATH_OR_NAME)
{
	T* res = FindOrNull<T>(RELATIVE_PATH_OR_NAME);
	Assert(!res, WCHAR_IS_NOT_NULLPTR);

	constexpr eResourceType RES_TYPE = engine_resource_type<T>::type;
	Dictionary& resources = mResources[static_cast<UINT>(RES_TYPE)];

	res = new T();

	const std::wstring FULL_PATH = PathManager::GetInstance()->GetResourcePath() + RELATIVE_PATH_OR_NAME;
	res->Load(FULL_PATH);

	res->mKey = RELATIVE_PATH_OR_NAME;
	res->mPath = RELATIVE_PATH_OR_NAME;

	resources.insert(std::make_pair(RELATIVE_PATH_OR_NAME, res)); //key : relative Path
}

template<typename T>
	requires (is_engine_resource<T>::value)
inline void ResourceManager::LoadByEnum(engine_resource_type<T>::eResEnumType resType)
{
	Load<T>(EnumResourcePath(resType));
}


template<typename T>
	requires (is_engine_resource<T>::value)
inline void ResourceManager::Insert(const Key& RELATIVE_PATH_OR_NAME, T* const value)
{
	Assert(value, WCHAR_IS_NULLPTR);
	constexpr eResourceType RES_TYPE = engine_resource_type<T>::type;

	Dictionary& resources = mResources[static_cast<UINT>(RES_TYPE)];
	ConstIterator citer = resources.find(RELATIVE_PATH_OR_NAME);

	Assert(resources.end() == citer, L"already");

	value->mKey = RELATIVE_PATH_OR_NAME;
	value->mPath = RELATIVE_PATH_OR_NAME;

	resources.insert(std::make_pair(RELATIVE_PATH_OR_NAME, value));
}
