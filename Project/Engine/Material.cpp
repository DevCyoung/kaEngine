#include "pch.h"
#include "Material.h"


Material::Material(const eRenderPriorityType type)
	: mShader(nullptr)
	, mTexture(nullptr)
	, mRenderType(type)
{
}

Material::~Material()
{
}

HRESULT Material::Load(const std::wstring& path)
{
	Assert(false, "");
	(void)path;
	return E_NOTIMPL;
}
