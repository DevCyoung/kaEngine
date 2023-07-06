#include "pch.h"
#include "Material.h"


Material::Material(const eRenderPriorityType RENDER_PRIORITY_TYPE)
	: mShader(nullptr)
	, mTexture(nullptr)
	, mRenderType(RENDER_PRIORITY_TYPE)
{
}

Material::~Material()
{
}

HRESULT Material::Load(const std::wstring& FULL_PATH)
{
	Assert(false, "");
	(void)FULL_PATH;
	return E_NOTIMPL;
}
