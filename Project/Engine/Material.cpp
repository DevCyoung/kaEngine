#include "pch.h"
#include "Material.h"
#include "Shader.h"
#include "Textrue.h"

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
		(void)path;
		return E_NOTIMPL;
	}
}