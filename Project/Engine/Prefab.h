#pragma once
#include "Resource.h"

class GameObject;

class Prefab : public Resource
{
public:
	Prefab(GameObject* obj);
	virtual ~Prefab();
	Prefab(const Prefab&) = delete;
	Prefab& operator=(const Prefab&) = delete;

	virtual HRESULT Load(const std::wstring& FULL_PATH) override final;

	GameObject* GetGameObject() const { Assert(mRoot, WCHAR_IS_NULLPTR); return mRoot; }

private:
	GameObject* mRoot;
};

