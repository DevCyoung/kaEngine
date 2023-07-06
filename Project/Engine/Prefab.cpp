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

HRESULT Prefab::Load(const std::wstring& FULL_PATH)
{
	(void)FULL_PATH;
	return E_NOTIMPL;
}
