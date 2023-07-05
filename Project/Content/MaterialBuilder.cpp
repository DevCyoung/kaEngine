#include "pch.h"
#include "MaterialBuilder.h"
#include "ResourceManager.h"

Material* MaterialBuilder::BuildDefault2DMaterial(const eRenderPriorityType renderType, 
	const std::wstring& shaderName, const eResTexture textureType)
{
	Material* const material = new Material(renderType);

	material->SetShader(gResourceManager
		->FindOrNull<Shader>(shaderName));
	material->SetTexture(gResourceManager
		->FindOrNullByEnum<Texture>(textureType));

	return material;
}
