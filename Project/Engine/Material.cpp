#include "pch.h"
#include "Material.h"

namespace engine
{
	Material::Material()
		: mShader(nullptr)
		, mTexture(nullptr)
	{
	}

	Material::~Material()
	{
	}

	HRESULT Material::Load(const std::wstring& path)
	{
		assert(false);
		(void)path;
		return E_NOTIMPL;
	}
}