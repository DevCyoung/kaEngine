#include "pch.h"
#include "Material.h"

Material::Material(const eRenderPriorityType renderPriorityType)
	: mShader(nullptr)
	, mTexture(nullptr)
	, mRenderType(renderPriorityType)
{
}

Material::~Material()
{
}

HRESULT Material::Load(const std::wstring& filePath)
{
	Assert(false, "");

	(void)filePath;
	return E_NOTIMPL;
}
