#include "pch.h"
#include "MaterialBuilder.h"
#include "ResourceManager.h"

Material* MaterialBuilder::BuildDefault2DMaterial(const eRenderPriorityType renderPriorityType, 
	const std::wstring& shaderKey, const eResTexture textureType)
{
	Material* const material = new Material(renderPriorityType);

	material->SetShader(gResourceManager
		->FindOrNull<Shader>(shaderKey));
	material->SetTexture(gResourceManager
		->FindOrNullByEnum<Texture>(textureType));

	return material;
}
