#include "pch.h"
#include "Prefab.h"
#include "GameObject.h"

Prefab::Prefab(GameObject* obj)
	: mRoot(obj)
{
}

Prefab::~Prefab()
{
	SAFE_DELETE_POINTER(mRoot);
}

HRESULT Prefab::Load(const std::wstring& path)
{
	(void)path;
	return E_NOTIMPL;
}
