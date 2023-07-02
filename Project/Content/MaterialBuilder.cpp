#include "pch.h"
#include "MaterialBuilder.h"
#include "ResourceManager.h"

Material* MaterialBuilder::BuildDefault2DMaterial(const eRenderType renderType, 
	const std::wstring& shaderName, const eResTexture textureType)
{
	Material* const material = new Material(renderType);

	material->SetShader(gResourceManager
		->FindOrNullByRelativePath<Shader>(shaderName));
	material->SetTexture(gResourceManager
		->FindOrNullByEnum<Texture>(textureType));

	return material;
}